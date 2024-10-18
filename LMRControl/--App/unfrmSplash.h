//---------------------------------------------------------------------------

#ifndef unfrmSplashH
#define unfrmSplashH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TFrmSplash : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
private:	// User declarations
public:		// User declarations
	__fastcall TFrmSplash(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmSplash *FrmSplash;
//---------------------------------------------------------------------------
#endif
