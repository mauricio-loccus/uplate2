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


__fastcall TFrmLabelAssignment::TFrmLabelAssignment(TComponent* Owner, WellMatrixList& wellMatrixListRef) : TForm(Owner)
{
	TTaskDialogBaseButtonItem* button;

	button = TaskDialog->Buttons->Add();
	button->Caption = "Sim";
	button->ModalResult = mrYes;

	button = TaskDialog->Buttons->Add();
	button->Caption = "N�o";
	button->ModalResult = mrNo;


	this->wellMatrixListRef = &wellMatrixListRef;
}


//---------------------------------------------------------------------------


void __fastcall TFrmLabelAssignment::InputData(std::vector<String> labels, int Row, int Column)
{
	String Values;

	std::vector<String>::iterator iterator = labels.begin();
	while(iterator != labels.end())
	{
		 LabelGrid->Cells[Column][Row] = *iterator;
		 Row++;
		 if (Row >= LabelGrid->RowCount)
		 {
			Row = 1;
			Column++;
			if (Column >= LabelGrid->ColCount)
			{
				break;
			}
		 }
		 ++iterator;
	}
}


//---------------------------------------------------------------------------


void __fastcall TFrmLabelAssignment::tsPlatesChange(TObject *Sender, int NewTab, bool &AllowChange)
{
	LabelGrid->Invalidate();
}


//---------------------------------------------------------------------------


void __fastcall TFrmLabelAssignment::LabelGridDrawWell(int ACol, int ARow, TRect &Rect, TWell& well)
{

}


//---------------------------------------------------------------------------


void __fastcall TFrmLabelAssignment::FormCreate(TObject *Sender)
{
	this->FileOpenDialog->InitialDir = GetCurrentDir();

	this->wellMatrixSelected = &(*wellMatrixListRef)[0];
	if (wellMatrixListRef->size() <= 0)
		return;

	std::vector<TWellMatrix>::iterator iterator;

	int largest = 0;
	iterator = this->wellMatrixListRef->begin();
	while( iterator != this->wellMatrixListRef->end() )
	{
		int length = iterator->Name.Length();
		largest = (largest > length) ? largest : length;
		iterator++;
	}

	iterator = this->wellMatrixListRef->begin();
	while( iterator != this->wellMatrixListRef->end() )
	{
		String Name = iterator->Name;

		String padding = "";
		padding = String(std::string((largest - Name.Length()) / 2 + 2, ' ').c_str());
		tsPlates->Tabs->Add(padding + Name + padding);
		++iterator;
	}
	tsPlates->TabIndex = 0;
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

		Message->Add(L"A importa��o ocorrer� a partir da c�lula atualmente selecionada.");
		Message->Add(L"");
		Message->Add(L"Gostaria de continuar?");

		TaskDialog->Text = Message->Text;
		TaskDialog->Execute();
		if (TaskDialog->ModalResult == mrNo)
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


void __fastcall TFrmLabelAssignment::LabelGridSetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value)
{
	wellMatrixListRef->at(tsPlates->TabIndex)[ARow - 1][ACol - 1].Label = Value;
}


//---------------------------------------------------------------------------


