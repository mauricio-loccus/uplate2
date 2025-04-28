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
	this->TaskDialog->Caption = L"Importação de Rótulos";
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


void __fastcall TFrmLabelAssignment::LabelGridSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
	CanSelect = true;
}


//---------------------------------------------------------------------------


void __fastcall TFrmLabelAssignment::LabelGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
	String   content;
	TCanvas* canvas = LabelGrid->Canvas;

	canvas = LabelGrid->Canvas;

	if (State.Contains(gdFixed))
	{
		if (ACol == 0 && ARow >= 1)
			content = AnsiChar('A' + ARow - 1);

		if (ARow == 0 && ACol >= 1)
			content = IntToStr(ACol);


        canvas->Font->Style = TFontStyles() << fsBold;
		canvas->Font->Size  = 12;

		canvas->Brush->Color = LabelGrid->FixedColor;
		canvas->FillRect(Rect);

		Integer pixelsTextWidth = canvas->TextWidth(content);
		Integer pixelsTextHeight = canvas->TextHeight(content);

		Integer textPosX = (Rect.Width() / 2 - pixelsTextWidth / 2);
		Integer textPosY = (Rect.Height() / 2 - pixelsTextHeight / 2);

		canvas->TextOut(Rect.Left + textPosX, Rect.Top + textPosY, content);

		return;
	}
}


//---------------------------------------------------------------------------



