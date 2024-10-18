//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "unWellsEdit.h"

#include "unDataModule.h"
#include "unInputFloatValue.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LMDBaseControl"
#pragma link "LMDBaseGraphicControl"
#pragma link "LMDBaseImage"
#pragma link "LMDCustomNImage"
#pragma link "LMDGraphicControl"
#pragma link "LMDNImage"
#pragma link "LMDBaseGraphicButton"
#pragma link "LMDCustomMMButton"
#pragma link "LMDMMButton"
#pragma link "LMDBaseLabel"
#pragma link "LMDCustomLabel"
#pragma link "LMDLabel"
#pragma resource "*.dfm"
TWellsEdit *WellsEdit;

typedef System::Set<TWellType, TWellType::wlEmpty, TWellType::wlPositiveControl> TWellTypeSet;

//---------------------------------------------------------------------------
__fastcall TWellsEdit::TWellsEdit(TComponent* Owner, Integer plateNum)
	: TFrame(Owner), selectedObject(btnEmpty),
	  currentObjSelected(0), selInterface(TSelectInterface::smMouse),
	  plateNumber(plateNum)
{
	controlEnabledArray.insert(std::make_pair(btnEmpty->Tag, False));
	controlEnabledArray.insert(std::make_pair(btnBlank->Tag, False));
	controlEnabledArray.insert(std::make_pair(btnNegControl->Tag, False));
	controlEnabledArray.insert(std::make_pair(btnPositiveControl->Tag, False));
	controlEnabledArray.insert(std::make_pair(btnQC->Tag, False));
	controlEnabledArray.insert(std::make_pair(btnStd->Tag, False));
	controlEnabledArray.insert(std::make_pair(btnUnknown->Tag, False));

	setCurrentObj(btnBlank);
}
//---------------------------------------------------------------------------
void __fastcall TWellsEdit::WellsGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
 	TWellMatrix& wellMatrixRef = (*TWellMatrixSingleton::instance())[plateNumber];

	TWell& w = (wellMatrixRef[ARow])[ACol];
	w.Row = ARow;
	w.Col = ACol;

	WellsGrid->Canvas->Brush->Color = clWhite;
	WellsGrid->Canvas->Pen->Style = psDot;
	WellsGrid->Canvas->Pen->Color = clWhite;

	WellsGrid->Canvas->Rectangle(Rect.Left, Rect.Top, Rect.Right, Rect.Bottom);

	MyDataModule->pngImageList->PNG[static_cast<Integer>(w.Type)+3]->Draw(WellsGrid->Canvas, Rect);

	if ((State.Contains(gdSelected) || State.Contains(gdHotTrack))
		&& controlEnabledArray[selectedObject->Tag])
	{
		if (selInterface == TSelectInterface::smKeyboard)
			return;

		if (drawMouseDown)
		{
			WellsGrid->Canvas->Brush->Color = clWhite;
			WellsGrid->Canvas->Pen->Style = psSolid;
			WellsGrid->Canvas->Pen->Color = clWhite;

			WellsGrid->Canvas->FrameRect(Rect);

			WellsGrid->Canvas->Pen->Style = psSolid;
			WellsGrid->Canvas->Pen->Color = clGray;
			WellsGrid->Canvas->Brush->Color = clGray;

			WellsGrid->Canvas->Rectangle(Rect.Left, Rect.Top, Rect.Right, Rect.Bottom);
		}

		if (static_cast<Integer>(w.Type) == selectedObject->Tag)
			MyDataModule->pngImageList->PNG[selectedObject->Tag+3]->Draw(WellsGrid->Canvas, Rect);
		else
			MyDataModule->pngImageList->PNG[static_cast<Integer>(w.Type)+3]->Draw(WellsGrid->Canvas, Rect);
	}

	drawWellText(WellsGrid->Canvas, Rect, w);
}
//---------------------------------------------------------------------------
void __fastcall TWellsEdit::drawWellText(TCanvas *canvas, const TRect& rect, const TWell& w)
{
	TWellTypeSet noReplicasFor = TWellTypeSet() << TWellType::wlEmpty << TWellType::wlBlank << TWellType::wlPositiveControl
												<< TWellType::wlNegativeControl;

	String wellTextType;

	canvas->Brush->Style = bsClear;
	canvas->Font->Color  = clWhite;

	switch (w.Type)
	{
		case TWellType::wlEmpty:
			break;

		case TWellType::wlBlank:
			wellTextType = "BR";
			canvas->Font->Color = clBlack;
			break;

		case TWellType::wlNegativeControl:
			wellTextType = "CN";
			break;

		case TWellType::wlPositiveControl:
			wellTextType = "CP";
			break;

		case TWellType::wlUnknown:
			wellTextType = "DC";
			break;

		case TWellType::wlConcentrationStd:
			wellTextType = "STD";
			break;

		case TWellType::wlQualityControl:
			wellTextType = "CQ";
			break;
	}

	Integer pixelsTextWidth = WellsGrid->Canvas->TextWidth(wellTextType);
	Integer pixelsTextHeight = WellsGrid->Canvas->TextHeight(wellTextType);

	Integer textPosX = (rect.Width() / 2 - pixelsTextWidth / 2);
	Integer textPosY = (rect.Height() / 2 - pixelsTextHeight / 2);

	Integer posY = textPosY;

	if (!noReplicasFor.Contains(w.Type))
		posY -=  (textPosY / 4);

	WellsGrid->Canvas->TextOut(rect.Left + textPosX, rect.Top + posY, wellTextType);

	if (!noReplicasFor.Contains(w.Type))
	{
		String value = IntToStr(w.ID);

		WellsGrid->Canvas->Font->Size = 8;

		pixelsTextWidth = WellsGrid->Canvas->TextWidth(value);
		pixelsTextHeight = WellsGrid->Canvas->TextHeight(value);

		textPosX = (rect.Width() / 2 - pixelsTextWidth / 2);
		textPosY = (rect.Height() / 2 - pixelsTextHeight / 2);

		WellsGrid->Canvas->TextOut(rect.Left + textPosX, rect.Bottom - textPosY, value);
	}
}
void __fastcall TWellsEdit::WellsGridDblClick(TObject *Sender)
{
 	TWellMatrix&  wellMatrixRef = (*TWellMatrixSingleton::instance())[plateNumber];

	Integer row = WellsGrid->Selection.Top;
	Integer col = WellsGrid->Selection.Left;

	TWell w = (wellMatrixRef[row])[col];
	if (w.Type != TWellType::wlConcentrationStd &&
		w.Type != TWellType::wlQualityControl)
		return;

	String caption = TEXT("Insira o valor do Padrão STD");

	if (w.Type == TWellType::wlQualityControl)
        caption = TEXT("Insira o valor do CQ");

	InputFloatValue = new TInputFloatValue(w, this);
	InputFloatValue->Caption = caption;
	Integer mr = InputFloatValue->ShowModal();
	InputFloatValue->Free();

	if (mrCancel == mr)
		return;

	wellMatrixRef.setAllReplicas(w);
}
//---------------------------------------------------------------------------
void __fastcall TWellsEdit::WellsGridKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	switch (Key)
	{
		case VK_UP:
		case VK_DOWN:
		case VK_LEFT:
		case VK_RIGHT:
			selInterface = TSelectInterface::smKeyboard;
			break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TWellsEdit::WellsGridMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	drawMouseDown = True;
}
//---------------------------------------------------------------------------
void __fastcall TWellsEdit::WellsGridMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	using System::Sysutils::Format;

	TWellTypeSet noReplicasFor = TWellTypeSet() << TWellType::wlEmpty << TWellType::wlBlank << TWellType::wlPositiveControl
												<< TWellType::wlNegativeControl;

	TWellMatrix&  wellMatrixRef = (*TWellMatrixSingleton::instance())[plateNumber];

	selInterface = TSelectInterface::smMouse;
	drawMouseDown = False;

	if (!controlEnabledArray[selectedObject->Tag])
		return;

	Integer hCells = (WellsGrid->Selection.Right - WellsGrid->Selection.Left)+1;
	Integer vCells = (WellsGrid->Selection.Bottom - WellsGrid->Selection.Top)+1;

	Integer countCells = hCells * vCells;

	TWellType type = static_cast<TWellType>(selectedObject->Tag);

	if (1 < countCells && !noReplicasFor.Contains(type))
	{
		CellOptions = new TCellOptions(cellOptions, this);
		Integer modalResult = CellOptions->ShowModal();
		CellOptions->Free();

		if (mrCancel == modalResult && !noReplicasFor.Contains(type))
			return;

		if ((countCells % cellOptions.replicas))
		{
			String msg = Format(TEXT("Número de réplicas (%d) incompatível com a quantidade\n")
								TEXT("de amostras selecionadas (%d)."),
								ARRAYOFCONST((cellOptions.replicas, countCells)));
			TaskMessageDlg(TEXT("Atenção"), msg, mtError, TMsgDlgButtons() << mbOK, 0);

			WellsGrid->Invalidate();
			return;
		}
	}

	for (Integer row = WellsGrid->Selection.Top; row <= WellsGrid->Selection.Bottom; row++)
	{
		for (Integer col = WellsGrid->Selection.Left; col <= WellsGrid->Selection.Right; col++)
		{
			const TWell& w = wellMatrixRef[row][col];

			if (w.Type != TWellType::wlEmpty)
			{
				String msg = Format(TEXT("Já existem poços designados dentro da área selecionada.\n")
									TEXT("Para realizar esta ação, por favor clique no botão \"Limpar\"."),
									ARRAYOFCONST((cellOptions.replicas, countCells)));
				TaskMessageDlg(TEXT("Atenção"), msg, mtWarning, TMsgDlgButtons() << mbOK, 0);

				WellsGrid->Invalidate();
				return;
			}
		}
	}

	Integer index = wellMatrixRef.getMaxWellTypeCount(type).ID;
	if (index >= WellsGrid->RowCount * WellsGrid->ColCount)
		index = 0;

	Integer replicas = cellOptions.replicas;

	if (cellOptions.enumDirection == TEnumerationDir::ndLeftRight)
	{
		for (Integer row = WellsGrid->Selection.Top; row <= WellsGrid->Selection.Bottom; row++)
			for (Integer col = WellsGrid->Selection.Left; col <= WellsGrid->Selection.Right; col++)
			{
				TWell& w = wellMatrixRef[row][col];

				if (w.Type == type)
					continue;

				w.PlateNumber = plateNumber;
				w.Type = type;
				w.ID = noReplicasFor.Contains(type)? 0: index+1;
				w.Col = col;
				w.Row = row;

				if (!--replicas)
				{
					++index;
					replicas = cellOptions.replicas;
				}
			}
	}
	else
	{
		for (Integer col = WellsGrid->Selection.Left; col <= WellsGrid->Selection.Right; col++)
			for (Integer row = WellsGrid->Selection.Top; row <= WellsGrid->Selection.Bottom; row++)
			{
				TWell& w = wellMatrixRef[row][col];

				if (w.Type == type)
					continue;

				w.PlateNumber = plateNumber;
				w.Type = type;
				w.ID = noReplicasFor.Contains(type)? 0: index+1;
				w.Col = col;
				w.Row = row;

				if (!--replicas)
				{
					++index;
					replicas = cellOptions.replicas;
				}
			}
	}

	WellsGrid->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TWellsEdit::setCurrentObj(TLMDMMButton *object)
{
	TLMDButtonFaceIndex bi;

	if (selectedObject != object)
	{
		bi = selectedObject->ButtonFaceIndex[Lmdbuttonbase::bsUp];
		bi.ListIndex = selectedObject->Tag;
		selectedObject->ButtonFaceIndex[Lmdbuttonbase::bsUp] = bi;

		controlEnabledArray[selectedObject->Tag] = False;
	}

	currentObjSelected = object->Tag;
	selectedObject = object;

	bi = selectedObject->ButtonFaceIndex[Lmdbuttonbase::bsUp];
	bi.ListIndex = selectedObject->Tag+1;
	selectedObject->ButtonFaceIndex[Lmdbuttonbase::bsUp] = bi;
	controlEnabledArray[object->Tag] = True;
}
void __fastcall TWellsEdit::btnEmptyClick(TObject *Sender)
{
	setCurrentObj(btnEmpty);
}
//---------------------------------------------------------------------------

void __fastcall TWellsEdit::btnNegControlClick(TObject *Sender)
{
	setCurrentObj(btnNegControl);
}
//---------------------------------------------------------------------------

void __fastcall TWellsEdit::btnPositiveControlClick(TObject *Sender)
{
	setCurrentObj(btnPositiveControl);
}
//---------------------------------------------------------------------------

void __fastcall TWellsEdit::btnStdClick(TObject *Sender)
{
	setCurrentObj(btnStd);
}
//---------------------------------------------------------------------------

void __fastcall TWellsEdit::btnQCClick(TObject *Sender)
{
	setCurrentObj(btnQC);
}
//---------------------------------------------------------------------------

void __fastcall TWellsEdit::btnUnknownClick(TObject *Sender)
{
	setCurrentObj(btnUnknown);
}
//---------------------------------------------------------------------------


void __fastcall TWellsEdit::btnBlankClick(TObject *Sender)
{
	setCurrentObj(btnBlank);
}
//---------------------------------------------------------------------------

void __fastcall TWellsEdit::btnClearClick(TObject *Sender)
{
 	TWellMatrix& wellMatrixRef = (*TWellMatrixSingleton::instance())[plateNumber];

    for (Integer row = 0; row < WellsGrid->RowCount; row++)
    {
		WellList& wlRef = wellMatrixRef[row];
        for (WellList::iterator cIt = wlRef.begin(); cIt != wlRef.end(); cIt++)
            *cIt = TWell();
    }

    WellsGrid->Invalidate();
}
//---------------------------------------------------------------------------



