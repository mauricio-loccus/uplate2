//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unRenamePlate.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmRenamePlate *FrmRenamePlate;
//---------------------------------------------------------------------------
__fastcall TFrmRenamePlate::TFrmRenamePlate(TComponent* Owner, String& newName)
	: TForm(Owner), newPlateName(newName)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmRenamePlate::btnOkClick(TObject *Sender)
{
	if (nameEdit->Text.Trim().IsEmpty())
	{
		MessageDlg("Insira o novo nome da placa ou clique no botão \"Cancelar\" abandonar.",
				   mtWarning, TMsgDlgButtons() << mbOK, 0);

		ModalResult = mrNone;
		return;
	}

	newPlateName = nameEdit->Text;
}
//---------------------------------------------------------------------------
