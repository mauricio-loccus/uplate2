//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unFrmFiltersEdit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LMDGrid"
#pragma resource "*.dfm"
TFrmFiltersEdit *FrmFiltersEdit;
//---------------------------------------------------------------------------
__fastcall TFrmFiltersEdit::TFrmFiltersEdit(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmFiltersEdit::colFilterValueFormatPaint(TObject *Grid, TLMDGridColumn *Column, const Variant &CellValue, bool IsNull,
		  TLMDString &ResultText)
{
	using System::Sysutils::Format;

	if (IsNull)
	{
		ResultText = "OFF";
		return;
	}

	Integer val = (Integer)CellValue;

	if (val == 0)
    {
		ResultText = "OFF";
		return;
	}

	ResultText = Format("%5dnm", ARRAYOFCONST((val)));
}
//---------------------------------------------------------------------------
void __fastcall TFrmFiltersEdit::FormShow(TObject *Sender)
{
	for (Integer i = 0; i < filtersEditGrid->DataRowCount; i++)
		filtersEditGrid->DeleteDataRow(i);

	filtersEditGrid->DataRowCount = FILTER_MAX;

	TLMDGridColumnTextParseEvent pe = colFilterValue->OnParse;
	colFilterValue->OnParse = NULL;

	for (Integer i = 0; i < FILTER_MAX; i++)
	{
		String sFilter(mFilters.filter[i]);

		filtersEditGrid->Cells[colFilterNumber->Position][i] = Variant(i+1);

		if (sFilter.UpperCase() == "OFF" ||
			sFilter.UpperCase() == "NO")
			sFilter = "0nm";

		if (!sFilter.IsEmpty())
			filtersEditGrid->Cells[colFilterValue->Position][i] = Variant(sFilter.SubString(0, sFilter.Length()-2).ToDouble());
	}

    colFilterValue->OnParse = pe;
	filtersEditGrid->CurrentRow = 0;
}
//---------------------------------------------------------------------------

void __fastcall TFrmFiltersEdit::colFilterValueParse(TObject *Grid, TLMDGridColumn *Column, TLMDString &TextValue, Variant &ResultValue,
		  bool &IsNull, bool &ParsedOk, PLMDString PErrMsg, bool CanRaiseError)
{
	if (filtersEditGrid->CurrentRow == 0)
		return;

	if (!ParsedOk)
	{
		*PErrMsg = String("Valor inválido para o filtro selecionado.");
		CanRaiseError = True;

		return;
	}

	Double value = 0;

	if (!IsNull)
	   value = ResultValue.AsType(varDouble);

	AnsiString sValue("OFF");

	if (value > 0)
		sValue = TextValue + "nm";

	ZeroMemory(mFilters.filter[filtersEditGrid->CurrentRow], sizeof(mFilters.filter[filtersEditGrid->CurrentRow]));
	strncpy(mFilters.filter[filtersEditGrid->CurrentRow], sValue.c_str(), sValue.Length());
}
//---------------------------------------------------------------------------

