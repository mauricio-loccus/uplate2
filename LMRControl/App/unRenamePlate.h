//---------------------------------------------------------------------------

#ifndef unRenamePlateH
#define unRenamePlateH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TFrmRenamePlate : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *nameEdit;
	TButton *btnOk;
	TButton *btnCancel;
	void __fastcall btnOkClick(TObject *Sender);
private:	// User declarations
	String& newPlateName;

public:		// User declarations
	__fastcall TFrmRenamePlate(TComponent* Owner, String& newName);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmRenamePlate *FrmRenamePlate;
//---------------------------------------------------------------------------
#endif
