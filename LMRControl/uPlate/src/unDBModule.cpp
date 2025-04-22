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
	Lmr96Connection->Params->Strings[keyIndex] = String("Database=") +  "Data\\µPlate.db3";

	String DatabasePath = Lmr96Connection->Params->Strings[keyIndex];
    String CurrentDirectory = GetCurrentDir();
}
//---------------------------------------------------------------------------

