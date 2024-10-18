//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unInputFloatValue.h"
//---------------------------------------------------------------------------
#pragma package(s#pragma link "LMDBaseEdit"
#pragma link "LMDControl"
#pragma link "LMDCustomBevelPanel"
#pragma link "LMDCustomComponent"
#pragma link "LMDCustomControl"
#pragma link "LMDCustomEdit"
#pragma link "LMDCustomMaskEdit"
#pragma link "LMDCustomPanel"
#pragma link "LMDMaskEdit"
#pragma link "LMDRegExpValidator"
#pragma link "LMDVldBase"

#pragma package(smart_init)
#pragma link "LMDEdit"
#pragma link "LMDFloatRangeValidator"
#pragma link "LMDErrorProvider"
#pragma link "LMDHintErrorProvider"
#pragma resource "*.dfm"

TInputFloatValue *InputFloatValue;

//---------------------------------------------------------------------------
__fastcall TInputFloatValue::TInputFloatValue(TWell& w, TComponent* Owner)
	: TForm(Owner), mWell(w)
{
}
//---------------------------------------------------------------------------
void __fastcall TInputFloatValue::btnOKClick(TObject *Sender)
{
	mWell.StdValue = StrToFloat(inputEdit->Text);

	if (0 > mWell.StdValue || 9999999.99 < mWell.StdValue)
	{
		MessageDlg(inputEdit->ValidationMsgString,
				   mtError,
				   TMsgDlgButtons() << mbClose,
				   0);

		mWell.StdValue = 0;
		ModalResult = mrCancel;
	}
}
//---------------------------------------------------------------------------
void __fastcall TInputFloatValue::FormShow(TObject *Sender)
{
	inputEdit->Text = FloatToStr(mWell.StdValue);
}
//---------------------------------------------------------------------------

