//---------------------------------------------------------------------------

#ifndef unKineticControlerH
#define unKineticControlerH

#include <System.hpp>
#include <System.Classes.hpp>

#include <cstdint>
#include <vector>
#include <memory>

#include "unElisaDevice.h"
#include "unParams.h"
#include "unWellMatrix.h"

typedef std::vector<TTime> KineticTimersList;
typedef std::vector<RawDataMatrix> KineticReadList;
typedef std::vector<TDateTime> TimeStampList;

typedef void __fastcall (__closure *TKineticDataArrivedEvent)(TObject *Sender, Word cicle);

class TKineticControler;

class TKineticControlerThread : public TThread
{
	public:
		__fastcall TKineticControlerThread(TKineticControler *owner, TElisaDevice *device, const KineticTimersList& rl);
		__fastcall ~TKineticControlerThread();

		inline const KineticReadList& __fastcall ResultList()
		{
			return mReadList;
		}

		__property TKineticDataArrivedEvent OnDataArrived = {read=onDataArrived, write=onDataArrived, stored=IsOnDataArrivedStored};
		__property Boolean Stop = {read=FStop, write=FStop, default=False};

	protected:
		void __fastcall Execute();

		void __fastcall OnReadDone(TObject *Sender, const RawDataMatrix& matrix, const RawDataMatrix& matrixFilter2);
		void __fastcall OnWaitTimerTimeout(TObject *Sender);

	private:
		inline Boolean IsOnDataArrivedStored()
		{
			return NULL != onDataArrived;
		}

	private:
		TElisaReadNotifyEvent mReadNotifyEvent;

		std::unique_ptr<TEvent> mReadEvent;
		std::unique_ptr<TTimer> mWaitTimer;

		ElisaParams *params;
		TElisaDevice *m_elisaDevice;
		KineticTimersList mTimersList;
		KineticReadList mReadList;
		TKineticControler *mOwner;
		TKineticDataArrivedEvent onDataArrived;

		Boolean FStop;
		Word mCurrentCicle;
};

typedef void __fastcall (__closure *TCurrentReadDoneEvent)(TObject *Sender);

class TKineticControler : public TComponent
{
	friend class TKineticControlerThread;

	public:
		__fastcall TKineticControler(TComponent *owner, TElisaDevice *device, const KineticTimersList& tl);
		__fastcall ~TKineticControler();

		__property TCurrentReadDoneEvent OnCurrentReadDone = {read=onCurrentReadDone, write=onCurrentReadDone, stored=IsCurrentReadDoneStored};

		TModalResult __fastcall Execute(TWellMatrix& wm);

	private:
		inline Boolean IsCurrentReadDoneStored()
		{
			return NULL != onCurrentReadDone;
		}

		void __fastcall CurrentCicleDone(TObject *Sender, Word cicle);
		void __fastcall DoAverageRateAlgorithm(TWellMatrix& wm);
		void __fastcall DoMaximumOfWellAlgorithm(TWellMatrix& wm, Boolean hasTimeElapsed = False, TTime elapsedTime = TTime());

	private:
		std::auto_ptr<TKineticControlerThread> mControlerThread;
		ElisaParams *m_elisaDeviceParams;
		TCurrentReadDoneEvent onCurrentReadDone;
		Word mTotalCicles;
		TimeStampList dataTimeStampList;
		KineticReadList readList;
		KineticTimersList mTimersList;
};
//---------------------------------------------------------------------------
#endif

