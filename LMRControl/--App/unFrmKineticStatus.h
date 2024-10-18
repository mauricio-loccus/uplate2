//---------------------------------------------------------------------------

#ifndef unFrmKineticStatusH
#define unFrmKineticStatusH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "unKineticControler.h"
#include <Vcl.ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TFrmKineticStatus : public TForm
{
	__published:	// IDE-managed Components
		TLabel *lbCurrentStatus;
		TButton *btnCancel;
		TLabel *lbTimestamp;
	TTimer *tmrKReadInterval;
		void __fastcall FormCreate(TObject *Sender);
		void __fastcall btnCancelClick(TObject *Sender);
	void __fastcall tmrKReadIntervalTimer(TObject *Sender);

	public:
		__property Word ReadingsTotal = {read=mLimit, write=mLimit, nodefault};

	private:	// User declarations
		Word mLimit;
		KineticTimersList mTimersList;
		TTime mCurrTime;
		KineticTimersList::size_type mTimeIndex;

	public:		// User declarations
		__fastcall TFrmKineticStatus(TComponent* Owner, const KineticTimersList& tl);

		void __fastcall UpdateCurrentStatus(Word current);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmKineticStatus *FrmKineticStatus;
//---------------------------------------------------------------------------
#endif
