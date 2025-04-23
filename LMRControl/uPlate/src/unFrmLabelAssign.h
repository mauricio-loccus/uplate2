//---------------------------------------------------------------------------

#ifndef unFrmLabelAssignH
#define unFrmLabelAssignH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------

#include "unWellMatrix.h"
#include <Vcl.Tabs.hpp>


class TFrmLabelAssignment : public TForm
{
__published:	// IDE-managed Components
	TButton*     btnClose;
	TButton*     btnImport;
	TStringGrid* LabelGrid;
	TTabSet*     tsPlates;

	//TButton *btnClearValues;
	//TButton *btnLoadCSV;
	//void __fastcall btnRandomClick(TObject *Sender);
	//void __fastcall btnClearValuesClick(TObject *Sender);
	//void __fastcall btnLoadCSVClick(TObject *Sender);

	//void __fastcall RawValuesGridSetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
	//void __fastcall RawValuesGridEnter(TObject *Sender);
	//void __fastcall RawValuesGridExit(TObject *Sender);

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btnCloseClick(TObject *Sender);
	void __fastcall btnImportClick(TObject *Sender);
	void __fastcall LabelGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);
	void __fastcall LabelGridSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);



	//void __fastcall RawValuesGridGetEditText(TObject *Sender, int ACol, int ARow, UnicodeString &Value);



private:	// User declarations
  WellMatrixList* wellMatrixListRef;
  TWellMatrix*    wellMatrixSelected;

public:		// User declarations
	__fastcall TFrmLabelAssignment(TComponent* Owner, WellMatrixList&);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmLabelAssignment *FrmLabelAssignment;
//---------------------------------------------------------------------------
#endif
