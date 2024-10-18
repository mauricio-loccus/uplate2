//---------------------------------------------------------------------------

#ifndef unInputFloatValueH
#define unInputFloatValueH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "LMDBaseEdit.hpp"
#include "LMDControl.hpp"
#include "LMDCustomBevelPanel.hpp"
#include "LMDCustomComponent.hpp"
#include "LMDCustomControl.hpp"
#include "LMDCustomEdit.hpp"
#include "LMDCustomMaskEdit.hpp"
#include "LMDCustomPanel.hpp"
#include "LMDMaskEdit.hpp"
#include "LMDRegExpValidator.hpp"
#include "LMDVldBase.hpp"
#include "LMDEdit.hpp"

#include "unWell.h"
#include "LMDFloatRangeValidator.hpp"
#include "LMDErrorProvider.hpp"
#include "LMDHintErrorProvider.hpp"

//---------------------------------------------------------------------------
class TInputFloatValue : public TForm
{
__published:	// IDE-managed Components
	TButton *btnOK;
	TButton *btnCancel;
	TLabel *Label1;
	TLMDMaskEdit *inputEdit;
	TLMDRegExpValidator *regExprValidator;
	TLMDHintErrorProvider *hintErrorProvider;
	void __fastcall btnOKClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
	TWell& mWell;

public:		// User declarations
	__fastcall TInputFloatValue(TWell& w, TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInputFloatValue *InputFloatValue;
//---------------------------------------------------------------------------
#endif
