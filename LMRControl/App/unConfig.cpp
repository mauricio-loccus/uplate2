//---------------------------------------------------------------------------
#include <VCL.h>
#include <System.IniFiles.hpp>

#include <memory>

#pragma hdrstop

#include "unConfig.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall AppConfig::AppConfig(TComponent *owner) : TComponent(owner),
                      mThousandSeparator(FormatSettings.ThousandSeparator),
                      mDecimalSeparator(FormatSettings.DecimalSeparator),
                      mHeadersInCsv(False),
                      mUserID(-1),
					  mIsRoot(False),
					  mSimulatorActive(False)
{
    Load();
}

__fastcall AppConfig::~AppConfig()
{
    Save();
}

void __fastcall AppConfig::Load()
{
    String cfgFName = ChangeFileExt(Application->ExeName, ".ini");

    if (FileExists(cfgFName, False))
        loadConfig(cfgFName);
}

void __fastcall AppConfig::Save()
{
    String cfgFName = ChangeFileExt(Application->ExeName, ".ini");
    saveConfig(cfgFName);
}
void __fastcall AppConfig::setThousandSeparator(WideChar separator)
{
    if (separator == mThousandSeparator)
        return;

    mThousandSeparator = separator;
}

void __fastcall AppConfig::setDecimalSeparator(WideChar separator)
{
    if (separator == mDecimalSeparator)
        return;

    mDecimalSeparator = separator;
}

void __fastcall AppConfig::setUserID(Largeint userID)
{
    if (mUserID == userID)
        return;

    mUserID = userID;
}

void __fastcall AppConfig::setUserLogin(String userLogin)
{
    if (mUserLogin == userLogin)
        return;

    mUserLogin = userLogin;
}

void __fastcall AppConfig::setUserName(String userName)
{
    if (mUserName == userName)
        return;

    mUserName = userName;
}

void __fastcall AppConfig::setIsRoot(Boolean isRoot)
{
    if (mIsRoot == isRoot)
        return;

    mIsRoot = isRoot;
}

void __fastcall AppConfig::setProtocolUnity(const String& unity)
{
    if (mProtoUnity == unity)
        return;

    mProtoUnity = unity;
}

void __fastcall AppConfig::setHeadersInCsv(Boolean set)
{
    if (mHeadersInCsv == set)
        return;

    mHeadersInCsv = set;
}

void __fastcall AppConfig::setSimulatorActive(Boolean set)
{
	if (mSimulatorActive == set)
		return;

	mSimulatorActive = set;
}

void __fastcall AppConfig::loadConfig(String cfgFName)
{
    std::unique_ptr<TIniFile> iniFile(new TIniFile(cfgFName));

    mDecimalSeparator = iniFile->ReadInteger(TEXT("CSV Settings"), TEXT("Decimal Separator"), FormatSettings.DecimalSeparator);
    mThousandSeparator = iniFile->ReadInteger(TEXT("CSV Settings"), TEXT("Thousand Separator"), FormatSettings.ThousandSeparator);
	mHeadersInCsv = iniFile->ReadBool(TEXT("CSV Settings"), TEXT("Include Headers"), False);
	mSimulatorActive = iniFile->ReadBool(TEXT("CSV Settings"), TEXT("Simulator Active"), False);
}

void __fastcall AppConfig::saveConfig(String cfgFName)
{
    std::unique_ptr<TIniFile> iniFile(new TIniFile(cfgFName));

    iniFile->WriteInteger(TEXT("CSV Settings"), TEXT("Decimal Separator"), mDecimalSeparator);
    iniFile->WriteInteger(TEXT("CSV Settings"), TEXT("Thousand Separator"), mThousandSeparator);
	iniFile->WriteBool(TEXT("CSV Settings"), TEXT("Include Headers"), mHeadersInCsv);
	iniFile->WriteBool(TEXT("CSV Settings"), TEXT("Simulator Active"), mSimulatorActive);
}

