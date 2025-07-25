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
	button->Caption = "Não";
	button->ModalResult = mrNo;


	this->wellMatrixListRef = &wellMatrixListRef;
}


//---------------------------------------------------------------------------


void __fastcall TFrmLabelAssignment::Next()
{
	int row;
	int col;


	int plate = tsPlates->TabIndex + 1;
	if (plate < 1 || plate > wellMatrixListRef->size())
		return;

	TWellMatrix& wellMatrix = wellMatrixListRef->at(plate - 1);

	row = LabelGrid->Row - 1;
	col = LabelGrid->Col - 1;

	int colCount = wellMatrix[row].size();
	while (col < colCount)
	{
		TWellType type;

		while ( row < wellMatrix.Rows )
		{
			type = wellMatrix[row][col].Type;
			if (type == TWellType::wlUnknown)
				break;

			row++;
		}

		type = wellMatrix[row][col].Type;
		if (wellMatrix[row][col].Type == TWellType::wlUnknown)
			break;

		row = 0;
		col++;
	}

	if (row < (LabelGrid->RowCount - 1) && col < (LabelGrid->ColCount - 1))
	{
		LabelGrid->Row = row + 1;
		LabelGrid->Col = col + 1;
	}

}


//---------------------------------------------------------------------------


void __fastcall TFrmLabelAssignment::InputData(std::vector<String> labels, int Row, int Column)
{
	int row;
	int col;
	int lastID;


	int plate = tsPlates->TabIndex + 1;
	if (plate < 1 || plate > wellMatrixListRef->size())
		return;

	TWellMatrix& wellMatrix = wellMatrixListRef->at(plate - 1);

	row = LabelGrid->Row - 1;
	col = LabelGrid->Col - 1;

	std::vector<String>::iterator iterator = labels.begin();

	int colCount = wellMatrix[row].size();
	while (col < colCount)
	{
		TWellType type;

		while ( row < wellMatrix.Rows )
		{
			type = wellMatrix[row][col].Type;
			if (type == TWellType::wlUnknown)
			{
				lastID = wellMatrix[row][col].ID;
				break;
			}


			row++;
		}

		while ( row < wellMatrix.Rows && iterator != labels.end() )
		{
			type = wellMatrix[row][col].Type;
			if (wellMatrix[row][col].Type == TWellType::wlEmpty)
			{
				wellMatrix[row][col].Type = TWellType::wlUnknown;
				wellMatrix[row][col].ID = lastID;
			}

			type = wellMatrix[row][col].Type;
			if (wellMatrix[row][col].Type == TWellType::wlUnknown)
			{
				if ( iterator != labels.end() )
				{
					wellMatrix[row][col].Label = *iterator;
					iterator++;
				}
			}

			row++;
		}

		row = 0;
		col++;
	}

	LabelGrid->Invalidate();

	/*
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


void __fastcall TFrmLabelAssignment::LabelGridDrawCell(TObject *Sender, int ACol, int ARow, TRect& Rect, TGridDrawState State)
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

	int plate = tsPlates->TabIndex + 1;
	if (plate < 1 || plate > wellMatrixListRef->size())
		return;

	this->LabelGridDrawWell(ACol, ARow, Rect, wellMatrixListRef->at(plate - 1)[ARow - 1][ACol - 1]);
}


//---------------------------------------------------------------------------


void __fastcall TFrmLabelAssignment::LabelGridDrawWell(int ACol, int ARow, TRect &Rect, TWell& well)
{
	this->LabelGridDrawWellFlavor_2(this->LabelGrid, ACol, ARow, Rect, well);
}


//---------------------------------------------------------------------------


void __fastcall TFrmLabelAssignment::LabelGridSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
	try
	{
		if (this->inEditor)
		{
			LabelGrid->EditorMode = false;
			this->inEditor = false;
		}

		if (ACol < 1 || ARow < 1)
		{
			 CanSelect = false;
			 return;
		}

		int plate = tsPlates->TabIndex + 1;
		if (plate < 1 || plate > wellMatrixListRef->size())
			return;

		TWell well = wellMatrixListRef->at(plate - 1)[ARow - 1][ACol - 1];
		CanSelect = (well.Type == TWellType::wlUnknown);
	}
	catch (...)
	{

	}
}


//---------------------------------------------------------------------------


void __fastcall TFrmLabelAssignment::LabelGridSetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value)
{
	this->inEditor = LabelGrid->EditorMode;
	if (this->inEditor)
		return;

	LabelGrid->Cells[ACol][ARow] = "";

	int plate = tsPlates->TabIndex + 1;
	if (plate < 1 || plate > wellMatrixListRef->size())
		return;

	wellMatrixListRef->at(plate - 1)[ARow - 1][ACol - 1].Label = Value;
}


//---------------------------------------------------------------------------


void __fastcall TFrmLabelAssignment::LabelGridGetEditText(TObject *Sender, int ACol, int ARow, UnicodeString &Value)
{
	int plate = tsPlates->TabIndex + 1;
	if (plate < 1 || plate > wellMatrixListRef->size())
		return;

	Value = wellMatrixListRef->at(plate - 1)[ARow - 1][ACol - 1].Label;
}


//---------------------------------------------------------------------------


void __fastcall TFrmLabelAssignment::LabelGridDrawUnknownWell_2_2(TStringGrid* LabelGrid, TRect& Rect, int id, String label)
{
	struct TRow {
		String  content;
		WORD    height;
		int     spacing;
	};

	TColor  background;
	TColor  foreground;
	Integer height;
	Integer padding;
	TRow    rows[2] = {
		{       "DC", 0, 4 },
		{ String(id), 0, 0 },
	};

	background = (TColor)RGB(0xde,0x41,0x7b);
	foreground = clWhite;

	TCanvas* canvas = LabelGrid->Canvas;

	if ( !label.IsEmpty() )
	{
		rows[0].content = rows[0].content + " " + rows[1].content;
		rows[1].content = label;
	}

	rows[0].height = canvas->TextHeight(rows[0].content);
	rows[1].height = canvas->TextHeight(rows[1].content);

	height = rows[0].height + 3 + rows[1].height;

	Rect.Inflate(-1, -1);
	padding = (Rect.Height() - height) / 2;

	canvas->Brush->Color = background;
	canvas->Pen->Color = clGray;
	canvas->RoundRect(Rect.Left-1, Rect.Top+1, Rect.Right-2, Rect.Bottom-1, 15, 15);

	Integer textPosY = padding;
	for(int i = 0; i < 2; i++)
	{
		if ( rows[i].content.IsEmpty() )
			continue;

		Integer textPosX = (Rect.Width() - canvas->TextWidth(rows[i].content)) / 2;
		canvas->Font->Color = foreground;
		canvas->TextOut(Rect.Left + textPosX, Rect.Top + textPosY, rows[i].content);

		textPosY += rows[i].height + rows[i].spacing;
	}
}


//---------------------------------------------------------------------------


void __fastcall TFrmLabelAssignment::LabelGridDrawUnknownWell_2_1(TStringGrid* LabelGrid, TRect& Rect, int id, String label)
{
	struct TRow {
		String  content;
		WORD    height;
		int     spacing;
	};

	TColor  background;
	TColor  foreground;
	Integer height;
	Integer padding;
	TRow    rows[3] = {
		{       "DC", 0, 1 },
		{ String(id), 0, 2 },
		{      label, 0, 0 }
	};

	background = (TColor)RGB(0xde,0x41,0x7b);
	foreground = clWhite;

	TCanvas* canvas = LabelGrid->Canvas;

	//rows[3].content = label;
	rows[0].height = canvas->TextHeight("DC");
	rows[1].height = canvas->TextHeight(String(id));

	height = rows[0].height + rows[0].spacing + rows[1].height;
	if ( !label.IsEmpty() )
	{
		rows[2].height = canvas->TextHeight(label);
		height += rows[1].spacing + rows[2].height;
	}

	Rect.Inflate(-1, -1);
	padding = (Rect.Height() - height) / 2;

	canvas->Brush->Color = background;
	canvas->Pen->Color = clGray;
	canvas->RoundRect(Rect.Left-1, Rect.Top+1, Rect.Right-2, Rect.Bottom-1, 11, 15);

	Integer textPosY = padding;
	for(int i = 0; i < 3; i++)
	{
		if ( rows[i].content.IsEmpty() )
			continue;

		Integer textPosX = (Rect.Width() - canvas->TextWidth(rows[i].content)) / 2;
		canvas->TextOut(Rect.Left + textPosX, Rect.Top + textPosY, rows[i].content);
		textPosY += rows[i].height + rows[i].spacing;
	}
}


//---------------------------------------------------------------------------


void __fastcall TFrmLabelAssignment::LabelGridDrawGeneric_2(TStringGrid* LabelGrid, TRect& Rect, TColor background, TColor foreground, String content)
{
	TCanvas* canvas = LabelGrid->Canvas;

	Rect.Inflate(-2,-4);

	canvas->Brush->Color = background;
	canvas->Pen->Color = clGray;
	canvas->RoundRect(Rect.Left-1, Rect.Top+1, Rect.Right-2, Rect.Bottom-1, 11, 15);

	canvas->Font->Color = foreground;
	Integer textPosX = (Rect.Width()  - canvas->TextWidth (content)) / 2;
	Integer textPosY = (Rect.Height() - canvas->TextHeight(content)) / 2;

	canvas->TextOut(Rect.Left + textPosX, Rect.Top + textPosY, content);
}


//---------------------------------------------------------------------------


void __fastcall TFrmLabelAssignment::LabelGridDrawWellFlavor_2(TStringGrid* LabelGrid, int ACol, int ARow, TRect &Rect, TWell& well)
{
	String   content;
	TColor   background;
	TColor   foreground;


	if (well.Type == TWellType::wlEmpty)
		return;

	if (well.Type == TWellType::wlUnknown)
	{
		this->LabelGridDrawUnknownWell_2_2(LabelGrid, Rect, well.ID, well.Label);
		return;
	}

	switch (well.Type)
	{
		case TWellType::wlEmpty:
			content = "";
			background = (TColor)RGB(0x00,0x30,0x00);
			foreground = clWhite;
			break;

		case TWellType::wlBlank:
			content = "BR";
			background =  TColor(0xffffff);
			foreground = clBlack;
			break;

		case TWellType::wlNegativeControl:
			content = "CN";
			background =  TColor(0x9c5163);
			foreground = clWhite;
			break;

		case TWellType::wlPositiveControl:
			content = "CP";
			background =  (TColor)RGB(0xff,0xcc,0x29);
			foreground = clBlack;
			break;

		case TWellType::wlConcentrationStd:
			content = "STD \n" + IntToStr(well.ID);
			background =  TColor(0x0055ff);
			foreground = clWhite;
			break;

	}

	this->LabelGridDrawGeneric_2(LabelGrid, Rect, background, foreground, content);
}


//---------------------------------------------------------------------------


void __fastcall TFrmLabelAssignment::LabelGridDrawWellFlavor_1(TStringGrid* LabelGrid, int ACol, int ARow, TRect &Rect, TWell& well)
{
	TCanvas* canvas = LabelGrid->Canvas;

	if (well.Type == TWellType::wlEmpty)
		return;

	canvas->TextOut(Rect.Left + 10, Rect.Top + 10, "abc");
}


//---------------------------------------------------------------------------


void __fastcall TFrmLabelAssignment::FormShow(TObject *Sender)
{
	 LabelGrid->SetFocus();
	 Next();
}


//---------------------------------------------------------------------------



