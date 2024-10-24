//---------------------------------------------------------------------------
#include <VCL.h>
#include <System.IniFiles.hpp>

#include <memory>

#pragma hdrstop

#include "unFileFilters.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall FileFilters::FileFilters(TComponent *owner) : TComponent(owner),
					  mFilter1("401"),
					  mFilter2("402"),
					  mFilter3("403"),
					  mFilter4("404"),
					  mFilter5(""),
					  mFilter6(""),
					  mFilter7(""),
					  mFilter8(""),
					  qtdFilterSet(4)
{
	Load();
}

__fastcall FileFilters::~FileFilters()
{
    Save();
}

void __fastcall FileFilters::Load()
{
    String cfgFName = ChangeFileExt(Application->ExeName, "_filters.ini");

    if (FileExists(cfgFName, False))
		loadConfig(cfgFName);
}

void __fastcall FileFilters::Save()
{
	String cfgFName = ChangeFileExt(Application->ExeName, "_filters.ini");
	saveConfig(cfgFName);
}


void __fastcall FileFilters::setFilters(TStringList *f)
{
	qtdFilterSet = 0;

	mFilter1 = "";
	mFilter2 = "";
	mFilter3 = "";
	mFilter4 = "";
	mFilter5 = "";
	mFilter6 = "";
	mFilter7 = "";
	mFilter8 = "";

	if (qtdFilterSet >= f->Count || f->Strings[qtdFilterSet] == "")
		return;
	mFilter1 = f->Strings[qtdFilterSet++];

	if (qtdFilterSet >= f->Count || f->Strings[qtdFilterSet] == "")
		return;
	mFilter2 = f->Strings[qtdFilterSet++];

	if (qtdFilterSet >= f->Count || f->Strings[qtdFilterSet] == "")
		return;
	mFilter3 = f->Strings[qtdFilterSet++];

	if (qtdFilterSet >= f->Count || f->Strings[qtdFilterSet] == "")
		return;
	mFilter4 = f->Strings[qtdFilterSet++];

	if (qtdFilterSet >= f->Count || f->Strings[qtdFilterSet] == "")
		return;
	mFilter5 = f->Strings[qtdFilterSet++];

	if (qtdFilterSet >= f->Count || f->Strings[qtdFilterSet] == "")
		return;
	mFilter6 = f->Strings[qtdFilterSet++];

	if (qtdFilterSet >= f->Count || f->Strings[qtdFilterSet] == "")
		return;
	mFilter7 = f->Strings[qtdFilterSet++];

	if (qtdFilterSet >= f->Count || f->Strings[qtdFilterSet] == "")
		return;
	mFilter8 = f->Strings[qtdFilterSet++];


}

void __fastcall FileFilters::getFilters(TStringList *f)
{
	if (mFilter1 == "")
	   return;
	f->Add(mFilter1);

	if (mFilter2 == "")
	   return;
	f->Add(mFilter2);

	if (mFilter3 == "")
	   return;
	f->Add(mFilter3);

	if (mFilter4 == "")
	   return;
	f->Add(mFilter4);

	if (mFilter5 == "")
	   return;
	f->Add(mFilter5);

	if (mFilter6 == "")
	   return;
	f->Add(mFilter6);

	if (mFilter7 == "")
	   return;
	f->Add(mFilter7);

	if (mFilter8 == "")
	   return;
	f->Add(mFilter8);
}



void __fastcall FileFilters::loadConfig(String cfgFName)
{
	std::unique_ptr<TIniFile> iniFile(new TIniFile(cfgFName));

	mFilter1 = iniFile->ReadString(TEXT("Filters"), TEXT("Filter1"), DEF_FILTER1);
	mFilter2 = iniFile->ReadString(TEXT("Filters"), TEXT("Filter2"), DEF_FILTER2);
	mFilter3 = iniFile->ReadString(TEXT("Filters"), TEXT("Filter3"), DEF_FILTER3);
	mFilter4 = iniFile->ReadString(TEXT("Filters"), TEXT("Filter4"), DEF_FILTER4);
	mFilter5 = iniFile->ReadString(TEXT("Filters"), TEXT("Filter5"), DEF_FILTER5);
	mFilter6 = iniFile->ReadString(TEXT("Filters"), TEXT("Filter6"), DEF_FILTER6);
	mFilter7 = iniFile->ReadString(TEXT("Filters"), TEXT("Filter7"), DEF_FILTER7);
	mFilter8 = iniFile->ReadString(TEXT("Filters"), TEXT("Filter8"), DEF_FILTER8);

	qtdFilterSet = 0;
	if (mFilter1 == "")
		return;
	qtdFilterSet++;
	if (mFilter2 == "")
		return;
	qtdFilterSet++;
	if (mFilter3 == "")
		return;
	qtdFilterSet++;
	if (mFilter4 == "")
		return;
	qtdFilterSet++;
	if (mFilter5 == "")
		return;
	qtdFilterSet++;
	if (mFilter6 == "")
		return;
	qtdFilterSet++;
	if (mFilter7 == "")
		return;
	qtdFilterSet++;
	if (mFilter8 == "")
		return;
	qtdFilterSet++;

}

void __fastcall FileFilters::saveConfig(String cfgFName)
{
	std::unique_ptr<TIniFile> iniFile(new TIniFile(cfgFName));

	iniFile->WriteString(TEXT("Filters"), TEXT("Filter1"), mFilter1);
	iniFile->WriteString(TEXT("Filters"), TEXT("Filter2"), mFilter2);
	iniFile->WriteString(TEXT("Filters"), TEXT("Filter3"), mFilter3);
	iniFile->WriteString(TEXT("Filters"), TEXT("Filter4"), mFilter4);
	iniFile->WriteString(TEXT("Filters"), TEXT("Filter5"), mFilter5);
	iniFile->WriteString(TEXT("Filters"), TEXT("Filter6"), mFilter6);
	iniFile->WriteString(TEXT("Filters"), TEXT("Filter7"), mFilter7);
	iniFile->WriteString(TEXT("Filters"), TEXT("Filter8"), mFilter8);
}

