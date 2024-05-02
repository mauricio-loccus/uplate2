//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unCellOptions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LMDBaseEdit"
#pragma link "LMDControl"
#pragma link "LMDCustomBevelPanel"
#pragma link "LMDCustomControl"
#pragma link "LMDCustomEdit"
#pragma link "LMDCustomExtSpinEdit"
#pragma link "LMDCustomMaskEdit"
#pragma link "LMDCustomPanel"
#pragma link "LMDSpinEdit"
#pragma resource "*.dfm"
TCellOptions *CellOptions;
//---------------------------------------------------------------------------
__fastcall TCellOptions::TCellOptions(TCellOptionsData& data, TComponent* Owner)
	: TForm(Owner), mCellOptions(data)
{
}
//---------------------------------------------------------------------------
void __fastcall TCellOptions::FormShow(TObject *Sender)
{
	rgEnumDirection->ItemIndex = static_cast<Integer>(mCellOptions.enumDirection);
	spnReplicas->Value = mCellOptions.replicas;
}
//---------------------------------------------------------------------------

void __fastcall TCellOptions::btnOkClick(TObject *Sender)
{
	mCellOptions.enumDirection = static_cast<TEnumerationDir>(rgEnumDirection->ItemIndex);
	mCellOptions.replicas = spnReplicas->Value;
}
//---------------------------------------------------------------------------

