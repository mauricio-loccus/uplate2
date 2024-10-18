//---------------------------------------------------------------------------
#include <vcl.h>

#pragma hdrstop

#include "unDBModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "Vcl.Controls.TControl"
#pragma resource "*.dfm"
TDBModule *DBModule;
//---------------------------------------------------------------------------
__fastcall TDBModule::TDBModule(TComponent* Owner)
	: TDataModule(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TDBModule::DataModuleCreate(TObject *Sender)
{
	Integer keyIndex = Lmr96Connection->Params->IndexOfName("Database");
	Lmr96Connection->Params->Strings[keyIndex] = "Database=" + ExtractFileDir(Application->ExeName) + "\\Data\\µPlate.db3";
}
//---------------------------------------------------------------------------

