//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unFrmWait.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFrmWait *FrmWait;
//---------------------------------------------------------------------------
__fastcall TFrmWait::TFrmWait(TWinControl *Owner, CallbackFunction *f)
	: TForm(Owner), mParent(Owner), functPointer(f), mGoalTime(60), mTimeToGoal(0),
	  mCloseTimeout(0)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmWait::tmrChronoTimer(TObject *Sender)
{
	mTimeToGoal++;
	StatusLabel->Caption = TEXT("Aguardando ") +
						   Format(TEXT("%2.2d:%2.2d"), ARRAYOFCONST((mTimeToGoal / 60, mTimeToGoal % 60))) +
						   TEXT("/") +
						   Format(TEXT("%2.2d:%2.2d"), ARRAYOFCONST((mGoalTime / 60, mGoalTime %60))) +
						   TEXT("...");

	if (mTimeToGoal >= mGoalTime)
	{
		tmrChrono->Enabled = False;
		StatusLabel->Caption = TEXT("Aguarde...");
	}
}
//---------------------------------------------------------------------------

void __fastcall TFrmWait::setTimePoint(const Longint seconds)
{
	mGoalTime = seconds;
	mCloseTimeout = mTimeToGoal = 0;
	tmrChrono->Enabled = True;
}

void __fastcall TFrmWait::tmrTimeoutTimer(TObject *Sender)
{
	if (++mCloseTimeout >= mGoalTime)
	{
		tmrTimeout->Enabled = False;
		StatusLabel->Caption = TEXT("Aguarde...");
	}
}
//---------------------------------------------------------------------------

void __fastcall TFrmWait::FormShow(TObject *Sender)
{
	mParent->Enabled = False;
	tmrTimeout->Enabled = True;
	mCloseTimeout = 0;
}
//---------------------------------------------------------------------------

void __fastcall TFrmWait::WndProc(Messages::TMessage& Msg)
{
    ancestor::WndProc(Msg);

    switch (Msg.Msg)
    {
        case FrmWaitMessages::WM_READ_FINISHED:
            ModalResult = mrOk;
            break;

        default:
            break;
    }
}

void __fastcall TFrmWait::FormClose(TObject *Sender, TCloseAction &Action)
{
	mParent->Enabled = True;
}
//---------------------------------------------------------------------------

void __fastcall TFrmWait::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	 if (Key == VK_ESCAPE)
	 {
		 Close();
	 }
}
//---------------------------------------------------------------------------

