//---------------------------------------------------------------------------

#ifndef unWellsEditH
#define unWellsEditH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "LMDBaseControl.hpp"
#include "LMDBaseGraphicControl.hpp"
#include "LMDBaseImage.hpp"
#include "LMDCustomNImage.hpp"
#include "LMDGraphicControl.hpp"
#include "LMDNImage.hpp"
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include "LMDBaseGraphicButton.hpp"
#include "LMDCustomMMButton.hpp"
#include "LMDMMButton.hpp"
#include "LMDBaseLabel.hpp"
#include "LMDCustomLabel.hpp"
#include "LMDLabel.hpp"

#include <map>

#include "unWellMatrix.h"

//---------------------------------------------------------------------------
enum class TSelectInterface : Integer
{
	smKeyboard = 0,
	smMouse = 1
};

class TWellsEdit : public TFrame
{
__published:	// IDE-managed Components
	TImage *imgLettersRule;
	TImage *imgNumbersRule;
	TLMDMMButton *btnEmpty;
	TLMDMMButton *btnBlank;
	TLMDMMButton *btnNegControl;
	TLMDMMButton *btnPositiveControl;
	TLMDMMButton *btnStd;
	TLMDMMButton *btnQC;
	TLMDMMButton *btnUnknown;
	TLMDMMButton *btnClear;
	TDrawGrid *WellsGrid;
	TLMDLabel *lbPlateCaption;
	void __fastcall WellsGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);
	void __fastcall WellsGridDblClick(TObject *Sender);
	void __fastcall WellsGridKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall WellsGridMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall WellsGridMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall btnEmptyClick(TObject *Sender);
	void __fastcall btnNegControlClick(TObject *Sender);
	void __fastcall btnPositiveControlClick(TObject *Sender);
	void __fastcall btnStdClick(TObject *Sender);
	void __fastcall btnQCClick(TObject *Sender);
	void __fastcall btnUnknownClick(TObject *Sender);
	void __fastcall btnBlankClick(TObject *Sender);
	void __fastcall btnClearClick(TObject *Sender);

protected:
	void __fastcall drawWellText(TCanvas *canvas, const TRect& rect, const TWell& w);

private:	// User declarations
	std::map<Integer, Boolean> controlEnabledArray;

	Boolean drawMouseDown;
	Integer currentObjSelected;
	Integer currentWellRow, currentWellCol;
	TLMDMMButton *selectedObject;

	TCellOptionsData cellOptions;
	TSelectInterface selInterface;

	Integer plateNumber;

	void __fastcall setCurrentObj(TLMDMMButton *object);

public:		// User declarations
	__fastcall TWellsEdit(TComponent* Owner, Integer plateNum);
};
//---------------------------------------------------------------------------
extern PACKAGE TWellsEdit *WellsEdit;
//---------------------------------------------------------------------------
#endif
