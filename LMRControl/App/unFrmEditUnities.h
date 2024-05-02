//---------------------------------------------------------------------------

#ifndef unFrmEditUnitiesH
#define unFrmEditUnitiesH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "LMDBaseControl.hpp"
#include "LMDBaseGraphicButton.hpp"
#include "LMDBaseGraphicControl.hpp"
#include "LMDCustomMMButton.hpp"
#include "LMDMMButton.hpp"
//---------------------------------------------------------------------------
class TFrmEditUnities : public TForm
{
__published:	// IDE-managed Components
	TEdit *edUnit;
	TLabel *Label1;
	TLMDMMButton *btnCancel;
	TLMDMMButton *btnApply;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnApplyClick(TObject *Sender);
	void __fastcall btnCancelClick(TObject *Sender);

private:	// User declarations
	String mUnity;
	System::Largeint mValue;

public:		// User declarations
	__fastcall TFrmEditUnities(TComponent* Owner);

	__property String Unity = {read = mUnity, write = mUnity};
	__property System::Largeint Value = {read = mValue, write = mValue};
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmEditUnities *FrmEditUnities;
//---------------------------------------------------------------------------
#endif
