//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TMainWindow : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TMainWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainWindow *MainWindow;
//---------------------------------------------------------------------------
#endif
