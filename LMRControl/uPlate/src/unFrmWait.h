//---------------------------------------------------------------------------

#ifndef unFrmWaitH
#define unFrmWaitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "LMDBaseControl.hpp"
#include "LMDBaseGraphicControl.hpp"
#include "LMDBaseMeter.hpp"
#include "LMDCustomProgress.hpp"
#include "LMDGraphicControl.hpp"
#include "LMDProgress.hpp"
#include <Vcl.ExtCtrls.hpp>
#include "SDL_ProgBar.hpp"
#include <Vcl.ComCtrls.hpp>

typedef void (__fastcall *CallbackFunction)(TWinControl *);

//---------------------------------------------------------------------------

enum class FrmWaitMessages : DWord
{
    WM_READ_FINISHED = WM_USER+2048
};

class TFrmWait : public TForm
{
    typedef TForm ancestor;

__published:	// IDE-managed Components
	TLabel *StatusLabel;
	TTimer *tmrChrono;
	TProgressBar *pgrBar;
	TTimer *tmrTimeout;
	void __fastcall tmrChronoTimer(TObject *Sender);
	void __fastcall tmrTimeoutTimer(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations
	Longint mGoalTime, mTimeToGoal;
	Longint mCloseTimeout;
	TWinControl *mParent;

	CallbackFunction *functPointer;

	void __fastcall WndProc(TMessage& Msg);

public:		// User declarations
	__fastcall TFrmWait(TWinControl *Owner, CallbackFunction *f = NULL);

	void __fastcall setTimePoint(const Longint seconds);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmWait *FrmWait;
//---------------------------------------------------------------------------
#endif
