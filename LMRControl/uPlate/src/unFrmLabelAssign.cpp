//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unFrmLabelAssign.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmLabelAssignment *FrmLabelAssignment;
//---------------------------------------------------------------------------
__fastcall TFrmLabelAssignment::TFrmLabelAssignment(TComponent* Owner, WellMatrixList& wellMatrixListRef) : TForm(Owner)
{
	this->wellMatrixListRef = &wellMatrixListRef;
}
//---------------------------------------------------------------------------

void __fastcall TFrmLabelAssignment::RawValuesGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
	TCanvas* canvas = RawValuesGrid->Canvas;
	String   content;
	TColor   color;

	if (State.Contains(gdFixed))
	{
		if (ACol == 0 && ARow >= 1)
			content = AnsiChar('A' + ARow - 1);

		if (ARow == 0 && ACol >= 1)
			content = IntToStr(ACol);



		canvas->Brush->Color = RawValuesGrid->FixedColor;
		canvas->FillRect(Rect);

		Integer pixelsTextWidth = canvas->TextWidth(content);
		Integer pixelsTextHeight = canvas->TextHeight(content);

		Integer textPosX = (Rect.Width() / 2 - pixelsTextWidth / 2);
		Integer textPosY = (Rect.Height() / 2 - pixelsTextHeight / 2);

		RawValuesGrid->Canvas->Font->Style = TFontStyles() << fsBold;
		RawValuesGrid->Canvas->Font->Size  = 12;

		canvas->TextOut(Rect.Left + textPosX, Rect.Top + textPosY, content);

		return;
	}

	content = "";
	color = clWhite;

	TWell& well = (*wellMatrixSelected)[ARow - 1][ACol - 1];
	switch (well.Type)
	{
		case TWellType::wlConcentrationStd:
			content = "STD" + IntToStr(well.ID);
			color = clYellow;
			break;

		case TWellType::wlPositiveControl:
			content = "CP";
			color = clGreen;
			break;

			//wlEmpty  = 0,
	//wlBlank  = 4,
	//wlNegativeControl = 8,
	//wlPositiveControl = 12,
	//wlQualityControl = 16,
	}
	//String s = RawValuesGrid->Cells[ACol][ARow];

	if (content.IsEmpty())
		return;

	//TCanvas *canvas = RawValuesGrid->Canvas;

	canvas->Brush->Color = color;
	canvas->FillRect(Rect);

	if (State.Contains(gdSelected))
		canvas->Brush->Color = clSkyBlue;

	if (State.Contains(gdFocused))
		canvas->DrawFocusRect(Rect);

	canvas->FillRect(Rect);

	Integer pixelsTextWidth = canvas->TextWidth(content);
	Integer pixelsTextHeight = canvas->TextHeight(content);

	Integer textPosX = (Rect.Width() / 2 - pixelsTextWidth / 2);
	Integer textPosY = (Rect.Height() / 2 - pixelsTextHeight / 2);

	canvas->TextOut(Rect.Left + textPosX, Rect.Top + textPosY, content);
}


void __fastcall TFrmLabelAssignment::btnCloseClick(TObject *Sender)
{
	ModalResult = mrClose;
}


//---------------------------------------------------------------------------
void __fastcall TFrmLabelAssignment::RawValuesGridSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
	if (ACol == 4 && ARow == 5)
	{
		CanSelect = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFrmLabelAssignment::FormCreate(TObject *Sender)
{
	this->wellMatrixSelected = &(*wellMatrixListRef)[0];

/*
	WellMatrixList& wellMatrixListRef = *TWellMatrixSingleton::instance();
	for (WellMatrixList::size_type i = 0; i < wellMatrixListRef.size(); i++)
	{
		TWellMatrix& wlp = wellMatrixListRef[i];

		for (Integer row = 0; row < m_elisaDeviceParams->PlateRows; row++)    //exibe corretamente os dados linha/coluna após leitura
		{
			TWell& w = wlp[row][0];

			for (WellList::iterator it = wlp[row].begin(); it != wlp[row].end(); it++)
			{
				if (it->Type != TWellType::wlConcentrationStd)
					it->StdValue = 0;

				it->RawValue = 0;
				it->RawValueFilter2 = 0;
				it->RawBlankReducedValue = 0;
				it->ConcentrationValue = 0;
			}
		}
	}
	*/
}
//---------------------------------------------------------------------------

