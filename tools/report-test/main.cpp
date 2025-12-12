//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "reportmodule.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"

TMainWindow *MainWindow;

//---------------------------------------------------------------------------

__fastcall TMainWindow::TMainWindow(TComponent* Owner) : TForm(Owner)
{
}

//---------------------------------------------------------------------------

void __fastcall TMainWindow::Button1Click(TObject *Sender)
{
	ReportsContainer->frxUserDataSetPlateMap->RangeEndCount = 4;   // ReadRawGrid->DataRowCount;
	ReportsContainer->frxReportPlateMap->PrepareReport();
	ReportsContainer->frxReportPlateMap->ShowPreparedReport();
}

//---------------------------------------------------------------------------

