//---------------------------------------------------------------------------

#ifndef unFrmProtocolH
#define unFrmProtocolH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TFrmProtocol : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TComboBox *cbProtocolName;
	TLabel *Label2;
	TMemo *MemoProtocolDescription;
	TButton *btnSave;
	TButton *Fechar;
	void __fastcall FormCreate(TObject *Sender);

private:	// User declarations

public:		// User declarations
	__fastcall TFrmProtocol(TComponent* Owner);

	System::Largeint __fastcall SaveNew(System::Largeint userID);
	void __fastcall UpdateRecord(System::Largeint userID, System::Largeint protocolID);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmProtocol *FrmProtocol;
//---------------------------------------------------------------------------
#endif
