//---------------------------------------------------------------------------

#ifndef unfrmPasswdH
#define unfrmPasswdH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include "LMDButton.hpp"
#include "LMDCustomButton.hpp"
#include "LMDBaseControl.hpp"
#include "LMDBaseGraphicButton.hpp"
#include "LMDBaseGraphicControl.hpp"
#include "LMDCustomMMButton.hpp"
#include "LMDMMButton.hpp"
//---------------------------------------------------------------------------
class TfrmPasswd : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TEdit *edPasswd;
	TLMDMMButton *btnOk;
	void __fastcall btnOKClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmPasswd(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPasswd *frmPasswd;
//---------------------------------------------------------------------------
#endif
