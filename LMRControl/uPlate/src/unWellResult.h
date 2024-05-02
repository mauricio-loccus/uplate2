//---------------------------------------------------------------------------

#ifndef unWellResultH
#define unWellResultH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------

#include "unWellMatrix.h"
#include "LMDBaseControl.hpp"
#include "LMDBaseGraphicControl.hpp"
#include "LMDBaseLabel.hpp"
#include "LMDCustomLabel.hpp"
#include "LMDLabel.hpp"

#include "unConfig.h"

enum TWellsShowOption : Integer
{
	shoAbsorbance = 0,
	shoConcentration,
	shoQualitative
};

typedef System::Set<TWellsShowOption, TWellsShowOption::shoAbsorbance, TWellsShowOption::shoQualitative> TWellsShowOptionFlags;

class TWellResult : public TFrame
{
__published:	// IDE-managed Components
	TImage *imgLettersRule;
	TImage *imgNumbersRule;
	TDrawGrid *WellsGrid;
	TLMDLabel *lbPlateCaption;
	void __fastcall WellsGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);

protected:
	void __fastcall drawWellText(TCanvas *canvas, const TRect& rect, const TWell& w);

private:	// User declarations
	TWellsShowOptionFlags mShowOptionsFlags;

    PAppConfig mpAppConfig;
    Integer mPlateNumber;

public:		// User declarations
	__fastcall TWellResult(TComponent* Owner, Integer plateNum, const TWellsShowOptionFlags& shoFlags);
};
//---------------------------------------------------------------------------
extern PACKAGE TWellResult *WellResult;
//---------------------------------------------------------------------------
#endif
