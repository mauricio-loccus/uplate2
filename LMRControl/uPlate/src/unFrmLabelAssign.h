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
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>


class TFrmLabelAssignment : public TForm
{
__published:	// IDE-managed Components
	TButton*             btnClose;
	TButton*             btnImport;
	TStringGrid*         LabelGrid;
	TTabSet*             tsPlates;
	TOpenTextFileDialog* FileOpenDialog;
	TTaskDialog*         TaskDialog;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btnCloseClick(TObject *Sender);
	void __fastcall btnImportClick(TObject *Sender);
	void __fastcall LabelGridDrawCell(TObject *Sender, int ACol, int ARow, TRect&, TGridDrawState);
	void __fastcall tsPlatesChange(TObject *Sender, int NewTab, bool &AllowChange);
	void __fastcall LabelGridSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall LabelGridSetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);

public:		// User declarations
	__fastcall TFrmLabelAssignment(TComponent* Owner, WellMatrixList&);

private:	// User declarations
	WellMatrixList* wellMatrixListRef;
	TWellMatrix*    wellMatrixSelected;

	void __fastcall InputData(std::vector<String>, int Row, int Column);
	void __fastcall LabelGridDrawWell(int ACol, int ARow, TRect &Rect, TWell& well);

	void __fastcall LabelGridDrawUnknownWell_2_2 (TStringGrid*, TRect&, int id, String);
	void __fastcall LabelGridDrawUnknownWell_2_1 (TStringGrid*, TRect&, int id, String);
	void __fastcall LabelGridDrawGeneric_2       (TStringGrid*, TRect& Rect, TColor, TColor foreground, String content);
	void __fastcall LabelGridDrawWellFlavor_2    (TStringGrid*, int ACol, int ARow, TRect &Rect, TWell& well);
	void __fastcall LabelGridDrawWellFlavor_1    (TStringGrid* LabelGrid, int ACol, int ARow, TRect &Rect, TWell&);

};

//---------------------------------------------------------------------------

extern PACKAGE TFrmLabelAssignment *FrmLabelAssignment;

//---------------------------------------------------------------------------

#endif
