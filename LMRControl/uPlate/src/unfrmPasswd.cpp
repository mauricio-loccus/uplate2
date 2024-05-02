//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unConfig.h"
#include "unfrmPasswd.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmPasswd *frmPasswd;

//---------------------------------------------------------------------------
__fastcall TfrmPasswd::TfrmPasswd(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmPasswd::btnOKClick(TObject *Sender)
{
	PAppConfig appCfg = AppConfigSingleton::instance();

	if (edPasswd->Text == TEXT("LoccusDebug"))
	{
		appCfg->setSimulatorActive(True);
		appCfg->Save();

		ModalResult = mrOk;

		return;
	}

	appCfg->setSimulatorActive(False);
	appCfg->Save();

	ModalResult = mrCancel;
}
//---------------------------------------------------------------------------


void __fastcall TfrmPasswd::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	switch (Key)
	{
		case VK_RETURN:
			btnOKClick(Sender);
			break;

		case VK_ESCAPE:
			ModalResult = mrCancel;
			break;
	}
}
//---------------------------------------------------------------------------


