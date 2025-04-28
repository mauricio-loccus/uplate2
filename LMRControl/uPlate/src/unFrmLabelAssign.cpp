//---------------------------------------------------------------------------

#include <vcl.h>
#include <Vcl.Dialogs.hpp>
#pragma hdrstop

#include "unFrmLabelAssign.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


TFrmLabelAssignment *FrmLabelAssignment;


//---------------------------------------------------------------------------


void __fastcall TFrmLabelAssignment::InputData(std::vector<String> labels, int Row, int Column)
{

}
//---------------------------------------------------------------------------


__fastcall TFrmLabelAssignment::TFrmLabelAssignment(TComponent* Owner, WellMatrixList& wellMatrixListRef) : TForm(Owner)
{
	this->TaskDialog = new TTaskDialog(this);
	this->wellMatrixListRef = &wellMatrixListRef;
}


//---------------------------------------------------------------------------


void __fastcall TFrmLabelAssignment::FormCreate(TObject *Sender)
{
	this->TaskDialog->Caption = L"Importaï¿½ï¿½o de Rï¿½tulos";
	this->TaskDialog->MainIcon = tdiWarning;
	this->TaskDialog->CommonButtons = TTaskDialogCommonButtons() << tcbYes << tcbNo;
	this->TaskDialog->DefaultButton = tcbNo;

	this->FileOpenDialog->InitialDir = GetCurrentDir();

	this->wellMatrixSelected = &(*wellMatrixListRef)[0];
}


//---------------------------------------------------------------------------


void __fastcall TFrmLabelAssignment::btnCloseClick(TObject *Sender)
{
	ModalResult = mrClose;
}


//---------------------------------------------------------------------------


void __fastcall TFrmLabelAssignment::btnImportClick(TObject *Sender)
{
	using namespace std;

	try
	{
		unique_ptr<TStringList> Message(new TStringList());

		Message->Add(L"A importação ocorrerá a partir da célula atualmente selecionada.");
		Message->Add(L"");
		Message->Add(L"Gostaria de continuar?");

		TaskDialog->Text = Message->Text;
		if (TaskDialog->Execute() == mrNo)
			return;

		if (!FileOpenDialog->Execute())
			return;

		TEncoding* encoding = TEncoding::UTF8;

		unique_ptr<TFileStream>   fileStream(new TFileStream(FileOpenDialog->FileName, fmOpenRead | fmShareExclusive));
		unique_ptr<TStreamReader> reader    (new TStreamReader( fileStream.get(), encoding ));

		vector<String> labels;
		while (!reader->EndOfStream)
		{
			labels.push_back(reader->ReadLine());
		}
		reader->Close();

		this->InputData(labels, LabelGrid->Row, LabelGrid->Col);
	}

	catch(Exception& exception)
	{
		Application->ShowException(&exception);
	}
}


//---------------------------------------------------------------------------


void __fastcall TFrmLabelAssignment::LabelGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
	TCanvas* canvas = LabelGrid->Canvas;
	String   content;
	TColor   color;

	if (State.Contains(gdFixed))
	{
		if (ACol == 0 && ARow >= 1)
			content = AnsiChar('A' + ARow - 1);

		if (ARow == 0 && ACol >= 1)
			content = IntToStr(ACol);



		canvas->Brush->Color = LabelGrid->FixedColor;
		canvas->FillRect(Rect);

		Integer pixelsTextWidth = canvas->TextWidth(content);
		Integer pixelsTextHeight = canvas->TextHeight(content);

		Integer textPosX = (Rect.Width() / 2 - pixelsTextWidth / 2);
		Integer textPosY = (Rect.Height() / 2 - pixelsTextHeight / 2);

		LabelGrid->Canvas->Font->Style = TFontStyles() << fsBold;
		LabelGrid->Canvas->Font->Size  = 12;

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


//---------------------------------------------------------------------------


void __fastcall TFrmLabelAssignment::LabelGridSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
	if (ACol == 4 && ARow == 5)
	{
		CanSelect = false;
	}
}


//---------------------------------------------------------------------------


