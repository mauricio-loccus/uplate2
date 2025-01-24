//---------------------------------------------------------------------------

#include <vcl.h>
#include <System.IOUtils.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.Dialogs.hpp>

#include <memory>
#pragma hdrstop

#include "unFrmSimulatedValues.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LMDGrid"
#pragma link "SDL_statis"
#pragma link "LMDCustomComponent"
#pragma link "LMDVistaDialogs"
#pragma resource "*.dfm"
TFrmSimulatedValues *FrmSimulatedValues;
//---------------------------------------------------------------------------
__fastcall TFrmSimulatedValues::TFrmSimulatedValues(RawDataMatrix& data, TComponent* Owner)
	: TForm(Owner), rawData(data), m_editingCol(-1), m_editingRow(-1)
{
}

//---------------------------------------------------------------------------
void __fastcall TFrmSimulatedValues::btnRandomClick(TObject *Sender)
{
	for (Integer col = 0; col < RawValuesGrid->ColCount-1; col++)
	{
		for (Integer row = 0; row < RawValuesGrid->RowCount-1; row++)
		{
			Single value = RandGen->Random;

			RawValuesGrid->Cells[col+1][row+1] = FloatToStrF(value, ffFixed, 6, 3);
			rawData[row][col] = value;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrmSimulatedValues::btnClearValuesClick(TObject *Sender)
{
	for (Integer col = 0; col < RawValuesGrid->ColCount-1; col++)
	{
		for (Integer row = 0; row < RawValuesGrid->RowCount-1; row++)
		{
			RawValuesGrid->Cells[col+1][row+1] = 0;
			rawData[row][col] = 0;
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TFrmSimulatedValues::btnLoadCSVClick(TObject *Sender)
{
    const String LoccusDataName("Loccus Biotecnologia");
	const String AppDataDirName = TPath::GetFileNameWithoutExtension(Application->ExeName);
    String UserAppData = GetEnvironmentVariable("APPDATA");
    String PublicAppData = GetEnvironmentVariable("PUBLIC");

	String AppDataDir = PublicAppData + TEXT("\\") + LoccusDataName + TEXT("\\") + AppDataDirName;

    std::unique_ptr<TOpenTextFileDialog> FileOpenDialog(new TOpenTextFileDialog(this));
    FileOpenDialog->Title = TEXT("Salvar Protocolo");
    FileOpenDialog->Filter = TEXT("Arquivo de dados RAW (*.csv)|*.csv");
    FileOpenDialog->DefaultExt = TEXT(".csv");
    FileOpenDialog->InitialDir = AppDataDir;

    if (!FileOpenDialog->Execute(Handle))
        return;

    String rawDataFile = FileOpenDialog->FileName;

    WideChar decSeparator = FormatSettings.DecimalSeparator;
    WideChar thSeparator  = FormatSettings.ThousandSeparator;

    if (m_appConfig->DecimalSeparator != FormatSettings.DecimalSeparator)
        FormatSettings.DecimalSeparator = m_appConfig->DecimalSeparator;

    if (m_appConfig->ThousandSeparator != FormatSettings.ThousandSeparator)
        FormatSettings.ThousandSeparator = m_appConfig->ThousandSeparator;

    TStringList *csvStringList = new TStringList();
    csvStringList->Delimiter = ';';

	btnClearValuesClick(Sender);

	LongWord fmOption = fmOpenRead | fmShareExclusive;

	TStreamReader *fStream = new TStreamReader(new TFileStream(rawDataFile, fmOption));

	try
	{
		for (Integer col = 0; col < RawValuesGrid->ColCount-1; col++)
		{
			csvStringList->DelimitedText = fStream->ReadLine();

			for (Integer row = 0; row < RawValuesGrid->RowCount-1 && !fStream->EndOfStream; row++)
			{
				RawValuesGrid->Cells[col+1][row+1] = 0;

				String value = (*csvStringList)[col];

				Single dummyValue = value.ToDouble();

				if (!value.IsEmpty())
					RawValuesGrid->Cells[col+1][row+1] = value;
			}

			csvStringList->Clear();
		}
	}
	catch (const EConvertError&)
	{
		TaskMessageDlg("Carregamento de valores CSV",
					   "Erro durante a conversão dos valores.\n"
					   "Verifique a aba \"Opções CSV\" na tela de preferências.",
					   mtError,
					   TMsgDlgButtons() << mbOK, 0);
	}

	csvStringList->Free();

	fStream->Close();

	fStream->BaseStream->Free();
	fStream->Free();
}

//---------------------------------------------------------------------------

void __fastcall TFrmSimulatedValues::FormCreate(TObject *Sender)
{
	m_appConfig = AppConfigSingleton::instance();

	for (Integer col = 0; col < RawValuesGrid->ColCount-1; col++)
	{
		for (Integer row = 0; row < RawValuesGrid->RowCount-1; row++)
			RawValuesGrid->Cells[col+RawValuesGrid->FixedCols][row+RawValuesGrid->FixedRows] = FloatToStrF(rawData[row][col], ffFixed, 6, 3);
	}
}
//---------------------------------------------------------------------------

void __fastcall TFrmSimulatedValues::btnCloseClick(TObject *Sender)
{
	for (Integer col = 0; col < RawValuesGrid->ColCount-1; col++)
	{
		for (Integer row = 0; row < RawValuesGrid->RowCount-1; row++)
			rawData[row][col] = RawValuesGrid->Cells[col+1][row+1].ToDouble();
	}

	ModalResult = mrClose;
}
//---------------------------------------------------------------------------

void __fastcall TFrmSimulatedValues::RawValuesGridSetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value)
{
	if (!RawValuesGrid->EditorMode)
	{
		try
		{
			Single v = Value.ToDouble();
		}
		catch (const EConvertError& e)
		{
			TaskMessageDlg(TEXT("Valor não permitido"),
						   TEXT("Por favor verifique o valor inserido, os valores devem ser numéricos com ponto decimal."),
						   mtError,
						   TMsgDlgButtons() << mbCancel, 0);

			RawValuesGrid->Col = m_editingCol;
			RawValuesGrid->Row = m_editingRow;
			RawValuesGrid->EditorMode = True;
			return;
		}

		m_editingCol = -1;
		m_editingRow = -1;

		return;
	}

	m_editingCol = ACol;
	m_editingRow = ARow;
}
//---------------------------------------------------------------------------

void __fastcall TFrmSimulatedValues::RawValuesGridEnter(TObject *Sender)
{
	m_editingCol = -1;
	m_editingRow = -1;
}
//---------------------------------------------------------------------------

void __fastcall TFrmSimulatedValues::RawValuesGridExit(TObject *Sender)
{
	if (m_editingCol != -1 && m_editingRow != -1)
	{
		RawValuesGrid->Col = m_editingCol;
		RawValuesGrid->Row = m_editingRow;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFrmSimulatedValues::RawValuesGridSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
	if (RawValuesGrid->EditorMode)
	{
		RawValuesGrid->EditorMode = False;

		if (m_editingCol != -1 && m_editingRow != -1)
		{
			RawValuesGridSetEditText(Sender, m_editingCol, m_editingRow, RawValuesGrid->Cells[m_editingCol][m_editingRow]);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TFrmSimulatedValues::RawValuesGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
	if (State.Contains(gdFixed))
	{
		String s;

		if (ACol == 0 && ARow >= 1)
			s = AnsiChar('A' + ARow - 1);

		if (ARow == 0 && ACol >= 1)
			s = IntToStr(ACol);

		TCanvas *canvas = RawValuesGrid->Canvas;

		canvas->Brush->Color = RawValuesGrid->FixedColor;
		canvas->FillRect(Rect);

		Integer pixelsTextWidth = canvas->TextWidth(s);
		Integer pixelsTextHeight = canvas->TextHeight(s);

		Integer textPosX = (Rect.Width() / 2 - pixelsTextWidth / 2);
		Integer textPosY = (Rect.Height() / 2 - pixelsTextHeight / 2);

		TFont *font = RawValuesGrid->Canvas->Font;

		font->Style = TFontStyles() << fsBold;

		canvas->TextOut(Rect.Left + textPosX, Rect.Top + textPosY, s);

		return;
	}

	String s = RawValuesGrid->Cells[ACol][ARow];

	if (s.IsEmpty())
		return;

	TCanvas *canvas = RawValuesGrid->Canvas;

	canvas->FillRect(Rect);

	if (State.Contains(gdSelected))
		canvas->Brush->Color = clSkyBlue;

	if (State.Contains(gdFocused))
		canvas->DrawFocusRect(Rect);

	canvas->FillRect(Rect);

	Integer pixelsTextWidth = canvas->TextWidth(s);
	Integer pixelsTextHeight = canvas->TextHeight(s);

	Integer textPosX = (Rect.Width() / 2 - pixelsTextWidth / 2);
	Integer textPosY = (Rect.Height() / 2 - pixelsTextHeight / 2);

	canvas->TextOut(Rect.Left + textPosX, Rect.Top + textPosY, s);
}
//---------------------------------------------------------------------------

void __fastcall TFrmSimulatedValues::RawValuesGridGetEditText(TObject *Sender, int ACol, int ARow, UnicodeString &Value)
{
	for (Integer i = 0; i < RawValuesGrid->ControlCount; i++)
	{
		if (RawValuesGrid->Controls[i]->ClassName() == "TInplaceEdit")
		{
			TInplaceEdit *ie = dynamic_cast<TInplaceEdit *>(RawValuesGrid->Controls[i]);

			ie->Alignment = System::Classes::taCenter;
		}
	}
}
//---------------------------------------------------------------------------

