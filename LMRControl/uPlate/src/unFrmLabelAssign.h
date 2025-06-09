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
	void __fastcall tsPlatesChange(TObject *Sender, int NewTab, bool &AllowChange);
	void __fastcall LabelGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);
	void __fastcall LabelGridSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);

public:		// User declarations
	__fastcall TFrmLabelAssignment(TComponent* Owner, WellMatrixList&);

private:	// User declarations
	WellMatrixList* wellMatrixListRef;
	TWellMatrix*    wellMatrixSelected;

	void __fastcall InputData(std::vector<String>, int Row, int Column);
	void __fastcall LabelGridDrawWell(int ACol, int ARow, TRect &Rect, TWell& well);

};

//---------------------------------------------------------------------------

extern PACKAGE TFrmLabelAssignment *FrmLabelAssignment;

//---------------------------------------------------------------------------

#endif
