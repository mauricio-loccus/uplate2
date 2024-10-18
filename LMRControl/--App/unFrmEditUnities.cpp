//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unFrmEditUnities.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LMDBaseControl"
#pragma link "LMDBaseGraphicButton"
#pragma link "LMDBaseGraphicControl"
#pragma link "LMDCustomMMButton"
#pragma link "LMDMMButton"
#pragma resource "*.dfm"
TFrmEditUnities *FrmEditUnities;
//---------------------------------------------------------------------------
__fastcall TFrmEditUnities::TFrmEditUnities(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmEditUnities::FormShow(TObject *Sender)
{
	edUnit->Text = Unity;
}
//---------------------------------------------------------------------------

void __fastcall TFrmEditUnities::btnApplyClick(TObject *Sender)
{
	mUnity = edUnit->Text.Trim();

	if (mUnity.IsEmpty())
	{
		MessageDlg("Unidade de medida obrigatório",
				   mtWarning,
				   TMsgDlgButtons() << mbOK, 0);

		return;
	}

	ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TFrmEditUnities::btnCancelClick(TObject *Sender)
{
	ModalResult = mrCancel;
}
//---------------------------------------------------------------------------
