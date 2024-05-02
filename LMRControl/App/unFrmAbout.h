//---------------------------------------------------------------------------

#ifndef unFrmAboutH
#define unFrmAboutH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include "LMDBaseControl.hpp"
#include "LMDBaseGraphicButton.hpp"
#include "LMDBaseGraphicControl.hpp"
#include "LMDCustomMMButton.hpp"
#include "LMDMMButton.hpp"
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------
class TFrmAbout : public TForm
{
__published:	// IDE-managed Components
    TImage *LogoLoccus;
	TLabel *lbBuildVersion;
	TSpeedButton *spdButtonLoccus;
	TLabel *lbCopyright;
	TButton *btnClose;
	TLabel *lbProdName;
	void __fastcall spdButtonLoccusClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
private:	// User declarations
public:		// User declarations
	__fastcall TFrmAbout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmAbout *FrmAbout;
//---------------------------------------------------------------------------
#endif
