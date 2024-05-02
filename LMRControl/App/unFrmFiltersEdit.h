//---------------------------------------------------------------------------

#ifndef unFrmFiltersEditH
#define unFrmFiltersEditH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "LMDGrid.hpp"
#include <Vcl.Grids.hpp>

#include "Elisa.h"

//---------------------------------------------------------------------------
class TFrmFiltersEdit : public TForm
{
__published:	// IDE-managed Components
	TLMDGrid *filtersEditGrid;
	TLMDGridTextColumn *colFilterNumber;
	TLMDGridFloatColumn *colFilterValue;
	TButton *btnSave;
	TButton *btnCancel;
	void __fastcall colFilterValueFormatPaint(TObject *Grid, TLMDGridColumn *Column, const Variant &CellValue, bool IsNull,
		  TLMDString &ResultText);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall colFilterValueParse(TObject *Grid, TLMDGridColumn *Column, TLMDString &TextValue, Variant &ResultValue,
          bool &IsNull, bool &ParsedOk, PLMDString PErrMsg, bool CanRaiseError);


	public:
		__property FILTERLUN Filters = {read = mFilters, write = mFilters};

	private:	// User declarations
		FILTERLUN mFilters;

	public:		// User declarations
		__fastcall TFrmFiltersEdit(TComponent* Owner);
};

//---------------------------------------------------------------------------
extern PACKAGE TFrmFiltersEdit *FrmFiltersEdit;
//---------------------------------------------------------------------------
#endif
