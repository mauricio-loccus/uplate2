//---------------------------------------------------------------------------

#ifndef unfrmSplashH
#define unfrmSplashH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>


//---------------------------------------------------------------------------

class TFrmSplash : public TForm
{
__published:	// IDE-managed Components
	TImage *Image;
	TTimer *CloseTimer;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall CloseTimerTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FormDestroy(TObject *Sender);

private:	// User declarations
public:		// User declarations
  __fastcall TFrmSplash::TFrmSplash(TComponent* Owner) : TForm(Owner) {}
};

//---------------------------------------------------------------------------
extern PACKAGE TFrmSplash *FrmSplash;
//---------------------------------------------------------------------------
#endif

