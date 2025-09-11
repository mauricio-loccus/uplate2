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
	TButton*             bApply;
	TButton*             bRevert;
	TButton*             btnImport;
	TStringGrid*         LabelGrid;
	TTabSet*             tsPlates;
	TOpenTextFileDialog* FileOpenDialog;
	TTaskDialog*         TaskDialog;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall bApplyClick(TObject *Sender);
	void __fastcall bRevertClick(TObject *Sender);
	void __fastcall btnImportClick(TObject *Sender);
	void __fastcall tsPlatesChange(TObject *Sender, int NewTab, bool &AllowChange);

	void __fastcall LabelGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);
	void __fastcall LabelGridSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall LabelGridSetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
	void __fastcall LabelGridGetEditText(TObject *Sender, int ACol, int ARow, UnicodeString &Value);
	void __fastcall LabelGridExitEditor(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall LabelGridMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);

public:		// User declarations
	__fastcall TFrmLabelAssignment(TComponent* Owner, WellMatrixList&);

private:	// User declarations
	struct  TStatus
	{
		int       plate;
		int       row;
		int       col;
		TWellType type;
		String    label;

		TStatus(int plate, int row, int col, TWellType type, const String& label);
	};

	std::vector<TStatus> Changes;

	WellMatrixList* wellMatrixListRef;
	TWellMatrix*    wellMatrixSelected;
	bool            inEditor;

	//bool __fastcall NextAllowed  (int plate, int& ARow, int& ACol, int options);
	//bool __fastcall ImportAllowed(int plate, int  ARow, int  ACol);
	void __fastcall InputDataOld(std::vector<String>, int& index);
	void __fastcall InputData(std::vector<String>, int& index, int plate, int row, int col);
	String __fastcall GetEllipsis(String text, TCanvas* canvas, int width);
	void __fastcall LabelGridDrawWell(int ACol, int ARow, TRect &Rect, TWell& well);

	TModalResult __fastcall QuestionDialog(TStringList* Message);

	void __fastcall LabelGridDrawUnknownWell_2_2 (TStringGrid*, TRect&, int id, String);
	void __fastcall LabelGridDrawUnknownWell_2_1 (TStringGrid*, TRect&, int id, String);
	void __fastcall LabelGridDrawGeneric_2       (TStringGrid*, TRect& Rect, TColor, TColor foreground, String content);
	void __fastcall LabelGridDrawWellFlavor_2    (TStringGrid*, int ACol, int ARow, TRect &Rect, TWell&);
	void __fastcall LabelGridDrawWellFlavor_1    (TStringGrid*, int ACol, int ARow, TRect &Rect, TWell&);

	void __fastcall MoveNextUnknown();

};

//---------------------------------------------------------------------------

extern PACKAGE TFrmLabelAssignment *FrmLabelAssignment;

//---------------------------------------------------------------------------

#endif
