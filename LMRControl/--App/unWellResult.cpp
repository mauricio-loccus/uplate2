//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unWellResult.h"
#include "unDataModule.h"
#include "unWellMatrix.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LMDBaseControl"
#pragma link "LMDBaseGraphicControl"
#pragma link "LMDBaseLabel"
#pragma link "LMDCustomLabel"
#pragma link "LMDLabel"
#pragma resource "*.dfm"
TWellResult *WellResult;
//---------------------------------------------------------------------------
__fastcall TWellResult::TWellResult(TComponent* Owner, Integer plateNum, const TWellsShowOptionFlags& shoFlags)
	: TFrame(Owner), mPlateNumber(plateNum), mShowOptionsFlags(shoFlags),
      mpAppConfig(AppConfigSingleton::instance())
{
}
//---------------------------------------------------------------------------
void __fastcall TWellResult::WellsGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
 	const TWellMatrix& wellMatrixRef = (*TWellMatrixSingleton::instance())[mPlateNumber];

	const TWell& w = (wellMatrixRef[ARow])[ACol];

	WellsGrid->Canvas->Brush->Color = clWhite;
	WellsGrid->Canvas->Pen->Style = psDot;
	WellsGrid->Canvas->Pen->Color = clWhite;

	WellsGrid->Canvas->Rectangle(Rect.Left, Rect.Top, Rect.Right, Rect.Bottom);

	MyDataModule->pngImageList->PNG[static_cast<Integer>(w.Type)+3]->Draw(WellsGrid->Canvas, Rect);

	drawWellText(WellsGrid->Canvas, Rect, w);
}
//---------------------------------------------------------------------------
void __fastcall TWellResult::drawWellText(TCanvas *canvas, const TRect& rect, const TWell& w)
{
	using System::Sysutils::Format;

	String wellTextId = Format("#%d", ARRAYOFCONST((w.ID)));

	Integer pixelsTextWidth = canvas->TextWidth(wellTextId);
	Integer pixelsTextHeight = canvas->TextHeight(wellTextId);
	Integer textPosX = (rect.Width() / 2 - pixelsTextWidth / 2);
	Integer textPosY = (rect.Height() / 4 - pixelsTextHeight / 4);

	Integer posY = textPosY / 2;

	canvas->Brush->Style = bsClear;

	switch (w.Type)
	{
		case TWellType::wlBlank:
			canvas->Font->Color = clWindowText;
			break;

		case TWellType::wlEmpty:
		case TWellType::wlNegativeControl:
		case TWellType::wlPositiveControl:
		case TWellType::wlUnknown:
		case TWellType::wlConcentrationStd:
		case TWellType::wlQualityControl:
			canvas->Font->Color = clWhite;
			break;
	}

	canvas->TextOut(rect.Left+textPosX, rect.Top + posY, wellTextId);

	posY = (rect.Height() / 2 - pixelsTextHeight / 2);

	if (mShowOptionsFlags.Contains(shoAbsorbance))
	{
		String wellValue = FloatToStrF(w.RawBlankReducedValue, ffNumber, 6, 3);

		pixelsTextWidth = canvas->TextWidth(wellValue);
		textPosX = (rect.Width() / 2 - pixelsTextWidth / 2);

		canvas->TextOut(rect.Left+textPosX, rect.Top + posY, wellValue);
	}

	if (mShowOptionsFlags.Contains(shoConcentration))
	{
		String wellValue = FloatToStrF(w.ConcentrationValue, ffNumber, 6, 3);

		Integer bkpFontSize = canvas->Font->Size;

		pixelsTextWidth  = canvas->TextWidth(wellValue);

		Single pixelSizeRatio = (Single)rect.Width() / (Single)pixelsTextWidth;

		canvas->Font->Size *= (pixelSizeRatio > 1)? 1.0: pixelSizeRatio;

		pixelsTextWidth = canvas->TextWidth(wellValue);

		textPosX = (rect.Width() / 2 - pixelsTextWidth / 2);
		textPosY = (rect.Height() / 4 - pixelsTextHeight / 4);

		canvas->TextOut(rect.Left+textPosX, rect.Top + posY, wellValue);

		canvas->Font->Size = bkpFontSize;
	}

	if (mShowOptionsFlags.Contains(shoQualitative))
	{
		String wellValue = Format("%s", ARRAYOFCONST((w.Interpret)));

		pixelsTextWidth = canvas->TextWidth(wellValue);
		textPosX = (rect.Width() / 2 - pixelsTextWidth / 2);

		canvas->TextOut(rect.Left+textPosX, rect.Top + posY, wellValue);
	}

	if (mShowOptionsFlags.Contains(TWellsShowOption::shoConcentration))
	{
		String unity = mpAppConfig->ProtocolUnity;
		pixelsTextWidth = WellsGrid->Canvas->TextWidth(unity);
        pixelsTextHeight = WellsGrid->Canvas->TextHeight(unity);

        textPosX = (rect.Width() / 2 - pixelsTextWidth / 2);
        textPosY = (rect.Height() / 2 - pixelsTextHeight / 2);

        canvas->TextOut(rect.Left + textPosX, rect.Bottom - textPosY, unity);
    }
}

