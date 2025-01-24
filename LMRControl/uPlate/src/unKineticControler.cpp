//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.DateUtils.hpp>
#include <algorithm>

#pragma hdrstop

#include "unKineticControler.h"
#include "unFrmKineticStatus.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TKineticControlerThread::TKineticControlerThread(TKineticControler *owner, TElisaDevice *device, const KineticTimersList& tl)
				: TThread(True),
				mTimersList(tl),
				params(ElisaParamsSingleton::instance()),
				m_elisaDevice(device),
				onDataArrived(NULL),
				mCurrentCicle(0),
				FStop(False),
				mOwner(owner)
{
	FreeOnTerminate = False;

	mReadNotifyEvent = m_elisaDevice->OnRead;
	m_elisaDevice->OnRead = TKineticControlerThread::OnReadDone;

	mWaitTimer.reset(new TTimer(owner));
	mWaitTimer->Enabled = False;
	mWaitTimer->OnTimer = TKineticControlerThread::OnWaitTimerTimeout;

	mReadEvent.reset(new TEvent((PSecurityAttributes)NULL, False, False, _T("KineticControlerThreadReadEvent"), False));
}

__fastcall TKineticControlerThread::~TKineticControlerThread()
{
	m_elisaDevice->OnRead = mReadNotifyEvent;
}

void __fastcall TKineticControlerThread::Execute()
{
	using System::Syncobjs::TWaitResult;

	KineticTimersList::iterator it;
	for (mCurrentCicle = 0; mCurrentCicle < static_cast<Word>(mTimersList.size()) && !FStop; ++mCurrentCicle)
	{
		Word hh, mm, ss, ms;
		mTimersList[mCurrentCicle].DecodeTime(&hh, &mm, &ss, &ms);

#ifdef _DEBUG
		m_elisaDevice->sendDoorCommand(True);
		do
		{
			m_elisaDevice->sendGetStatus();
			Sleep(50);
		} while(m_elisaDevice->RunMode != ElisaDeviceRunModeStatus::ElisaDeviceRunMode_IDLE);

		MessageDlg("Troque a placa e pressione \"Ok\" para continuar.",
				   mtInformation,
				   TMsgDlgButtons() << mbOK, 0);

		m_elisaDevice->sendDoorCommand(False);
		do
		{
			m_elisaDevice->sendGetStatus();
			Sleep(50);
		} while(m_elisaDevice->RunMode != ElisaDeviceRunModeStatus::ElisaDeviceRunMode_IDLE);
#endif

		Integer waitMs = ((hh * 3600) + (mm * 60) + ss) * 1000;

		mWaitTimer->Interval = waitMs;
		mWaitTimer->Enabled = True;
		m_elisaDevice->sendSetParams();

		if (FrmKineticStatus)
			FrmKineticStatus->UpdateCurrentStatus(mCurrentCicle);

		TWaitResult swr;
		while (TWaitResult::wrSignaled != (swr = mReadEvent->WaitFor(20)))
		{
			if (FStop)
			{
				mWaitTimer->Enabled = False;
				break;
			}
		}
	}
}

void __fastcall TKineticControlerThread::OnWaitTimerTimeout(TObject *Sender)
{
	mWaitTimer->Enabled = False;

	Synchronize(m_elisaDevice->sendRunProgram);
	mReadEvent->SetEvent();
}

void __fastcall TKineticControlerThread::OnReadDone(TObject *Sender, const RawDataMatrix& matrix, const RawDataMatrix& matrixFilter2)
{
	mReadList.push_back(matrix);

	if (IsOnDataArrivedStored())
		OnDataArrived(Sender, mCurrentCicle);
}

__fastcall TKineticControler::TKineticControler(TComponent *owner, TElisaDevice *device, const KineticTimersList& tl) :
				TComponent(owner),
				mControlerThread(new TKineticControlerThread(this, device, tl)),
				m_elisaDeviceParams(ElisaParamsSingleton::instance()),
				mTimersList(tl),
				mTotalCicles(tl.size())
{
	mControlerThread->OnDataArrived = TKineticControler::CurrentCicleDone;
}

__fastcall TKineticControler::~TKineticControler()
{
}

TModalResult __fastcall TKineticControler::Execute(TWellMatrix& wm)
{
	TTime startTime = Now();
	mControlerThread->Suspended = False;

	__try
	{
		FrmKineticStatus = new TFrmKineticStatus(this, mTimersList);
		FrmKineticStatus->ShowModal();

		if (FrmKineticStatus->ModalResult == mrCancel)
		{
			mControlerThread->Stop = True;
			mControlerThread->WaitFor();

			return mrCancel;
		}
	}
	__finally
	{
		FrmKineticStatus->Free();
		FrmKineticStatus = NULL;
	}

	readList = mControlerThread->ResultList();

	switch (m_elisaDeviceParams->KineticParams.Type)
	{
		case TElisaKineticType::AverageRate:
			DoAverageRateAlgorithm(wm);
			break;

		case TElisaKineticType::MaximumOfWell:
			DoMaximumOfWellAlgorithm(wm);
			break;

		case TElisaKineticType::TimeToMaximum:
			DoMaximumOfWellAlgorithm(wm, True, startTime);
			break;

		default:
			break;
	}

	return mrClose;
}

void __fastcall TKineticControler::CurrentCicleDone(TObject *Sender, Word cicle)
{
	dataTimeStampList.push_back(Now());

	FrmKineticStatus->tmrKReadInterval->Enabled = False;

	if (cicle+1 < mTimersList.size())
		return;

	if (IsCurrentReadDoneStored())
		OnCurrentReadDone(this);

	FrmKineticStatus->ModalResult = mrClose;
}

void __fastcall TKineticControler::DoAverageRateAlgorithm(TWellMatrix& wm)
{
	TDateTime first = dataTimeStampList.front();
	TDateTime last  = dataTimeStampList.back();

	TTime interval = last - first;

	Single totalIntervalValue = (HourOf(interval) * 3600) + (MinuteOf(interval) * 60) + SecondOf(interval);

	if (m_elisaDeviceParams->KineticParams.RateType == TElisaKineticRateType::Minutes)
		totalIntervalValue /= 60.0;

	RawDataMatrix raw = RawDataMatrix();

	for (KineticReadList::iterator kit = readList.begin(); kit != readList.end(); ++kit)
	{
		for (Integer col = 0; col < m_elisaDeviceParams->PlateCols; col++)
		{
			for (Integer row = 0; row < m_elisaDeviceParams->PlateRows; row++)
				raw[row][col] += (*kit)[row][col];
		}
	}

	TWell& w = wm[0][0];

	for (Integer col = 0; col < m_elisaDeviceParams->PlateCols; col++)
	{
		for (Integer row = 0; row < m_elisaDeviceParams->PlateRows; row++)
		{
			w = wm[row][col];
			w.RawValue = raw[row][col] / totalIntervalValue;
		}
	}
}

void __fastcall TKineticControler::DoMaximumOfWellAlgorithm(TWellMatrix& wm, Boolean hasTimeElapsed, TTime elapsedTime)
{

	for (Integer col = 0; col < m_elisaDeviceParams->PlateCols; col++)
	{
		 for (Integer row = 0; row < m_elisaDeviceParams->PlateRows; row++)
		{
			std::vector<Single> wellMaxValueList;

			for (KineticReadList::size_type i = 0; i < readList.size(); i++)
			{
				Single readValue = 0;

				readValue = (readList[i])[row][col];
				wellMaxValueList.push_back(readValue);
			}

			TWell& w = wm[row][col];

			std::vector<Single>::const_iterator it = std::max_element(wellMaxValueList.begin(), wellMaxValueList.end());

			Single rawValue = *it;

			w.RawValue = rawValue;

			if (hasTimeElapsed)
			{
				Integer pos = it - wellMaxValueList.begin();
				TTime moment = dataTimeStampList[pos] - elapsedTime;

				w.Timestamp = moment;
			}
		}
	}
}

