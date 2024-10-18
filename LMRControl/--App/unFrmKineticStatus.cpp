//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unFrmKineticStatus.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const Double SECONDSINADAY = (3600 * 24);

TFrmKineticStatus *FrmKineticStatus;
//---------------------------------------------------------------------------
__fastcall TFrmKineticStatus::TFrmKineticStatus(TComponent* Owner, const KineticTimersList& tl)
	: TForm(Owner), mLimit(tl.size()), mTimersList(tl), mCurrTime(0),
	  mTimeIndex(0)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmKineticStatus::FormCreate(TObject *Sender)
{
	using System::UnicodeString::Format;

	lbCurrentStatus->Caption = Format("Leitura  1/%d", ARRAYOFCONST((mLimit)));

	lbTimestamp->Visible = True;
}
//---------------------------------------------------------------------------

void __fastcall TFrmKineticStatus::UpdateCurrentStatus(Word current)
{
	using System::UnicodeString::Format;

	tmrKReadInterval->Enabled = False;

	mTimeIndex = current;
	lbCurrentStatus->Caption = Format("Leitura %2d/%d", ARRAYOFCONST((current+1, mLimit)));

	mCurrTime = TTime(0);

	tmrKReadInterval->Enabled = True;
}

void __fastcall TFrmKineticStatus::btnCancelClick(TObject *Sender)
{
	ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TFrmKineticStatus::tmrKReadIntervalTimer(TObject *Sender)
{
	mCurrTime += static_cast<Double>(1.0/SECONDSINADAY);

	String sKReadCurrentTime = FormatDateTime(TEXT("hh:nn:ss"), mCurrTime);
	String sKReadInterval = FormatDateTime(TEXT("hh:nn:ss"), mTimersList[mTimeIndex]);

	if (mCurrTime > mTimersList[mTimeIndex])
		return;

	lbTimestamp->Caption = sKReadCurrentTime + TEXT("/") + sKReadInterval;
}
//---------------------------------------------------------------------------

