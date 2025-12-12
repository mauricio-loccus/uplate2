//---------------------------------------------------------------------------


#pragma hdrstop

#include "reportmodule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "Vcl.Controls.TControl"
#pragma link "frxClass"
#pragma resource "*.dfm"
TReportsContainer *ReportsContainer;
//---------------------------------------------------------------------------
__fastcall TReportsContainer::TReportsContainer(TComponent* Owner)
	: TDataModule(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TReportsContainer::frxUserDataSetPlateMapCheckEOF(TObject *Sender, bool &Eof)
{
    Eof = frxUserDataSetPlateMap->RecNo > 90;
}
//---------------------------------------------------------------------------

