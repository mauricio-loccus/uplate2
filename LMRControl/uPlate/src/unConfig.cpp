//---------------------------------------------------------------------------
#include <VCL.h>
#include <System.IniFiles.hpp>

#include <memory>
#include <iostream>

#include <System.IOUtils.hpp>

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
					  mSimulatorActive(False), mVersion2023 (True)
{
	try
	{
		mDataDirectory = TPath::GetTempPath();
	}
	catch (const EOSError &exception)
	{
		std::cerr << "[ERROR]:Fail on take temporary path" << std::endl;
	}

	Load();
}

__fastcall AppConfig::~AppConfig()
{
	Save();
}

void __fastcall AppConfig::Load()
{
	String cfgFName = ChangeFileExt(ExtractFileName(Application->ExeName), ".ini");
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

void __fastcall AppConfig::setVersion2023(Boolean set)
{
	if (mVersion2023 == set)
		return;

	mVersion2023 = set;
}

String __fastcall AppConfig::GetDataDirectory()
{
	const String LoccusDataName("Loccus Biotecnologia");

	String UserAppData;
	String PublicAppData;

	String AppName = TPath::GetFileNameWithoutExtension(Application->ExeName);
	UserAppData    = GetEnvironmentVariable("APPDATA");
	PublicAppData  = GetEnvironmentVariable("PUBLIC");

	String DataDirectory = PublicAppData + L"\\" + LoccusDataName + L"\\" + AppName;

	return DataDirectory;
}

String __fastcall AppConfig::ExpandEnvironment(String path)
{
	TCHAR  buffer[MAX_PATH];
	String expanded;

	DWORD result = ExpandEnvironmentStrings(path.c_str(), buffer, MAX_PATH);
	if (result == 0 || result > MAX_PATH)
		throw Exception("[ERROR]:Environment variable not found");

	expanded = String(buffer);

	enum class Variables { Search, Inside, Error } status = Variables::Search;

	String unresolved;
	int begin;
	int position = 0;
	while (position < expanded.Length())
	{
		switch (expanded[position + 1])
		{
			case '%':
				switch (status)
				{
					case Variables::Search:
						status = Variables::Inside;
						begin = position + 1;
						break;

					case Variables::Inside:
						status = Variables::Search;
						unresolved += (!unresolved.IsEmpty() ? "," : "") + expanded.SubString(begin - 1, position - begin + 2);
						break;

				}
				break;

			default:
				break;

		}

		position++;
		if ((position == expanded.Length() - 1) && (status == Variables::Inside))
		{
			unresolved += (!unresolved.IsEmpty() ? "," : "") + expanded.SubString(begin, position - begin + 1);
		}
	}

	if (!unresolved.IsEmpty())
		throw Exception("[ERROR]:Unresolved Environment variables: " + unresolved);

	return expanded;
}

void __fastcall AppConfig::loadConfig(String cfgFName)
{
	std::unique_ptr<TIniFile> iniFile(new TIniFile(GetCurrentDir() + "\\" + cfgFName));

	mDecimalSeparator = iniFile->ReadInteger(TEXT("CSV Settings"), TEXT("Decimal Separator"), FormatSettings.DecimalSeparator);
	mThousandSeparator = iniFile->ReadInteger(TEXT("CSV Settings"), TEXT("Thousand Separator"), FormatSettings.ThousandSeparator);
	mHeadersInCsv = iniFile->ReadBool(TEXT("CSV Settings"), TEXT("Include Headers"), False);
	mSimulatorActive = iniFile->ReadBool(TEXT("CSV Settings"), TEXT("Simulator Active"), False);
	mVersion2023 = iniFile->ReadBool(TEXT("Main Settings"), TEXT("Version2023"), True);

	mDataDirectory = ExpandEnvironment(iniFile->ReadString(TEXT("Directories"), TEXT("Data"), GetDataDirectory()));
}

void __fastcall AppConfig::saveConfig(String cfgFName)
{
	std::unique_ptr<TIniFile> iniFile(new TIniFile(cfgFName));

	iniFile->WriteInteger(TEXT("CSV Settings"), TEXT("Decimal Separator"), mDecimalSeparator);
	iniFile->WriteInteger(TEXT("CSV Settings"), TEXT("Thousand Separator"), mThousandSeparator);
	iniFile->WriteBool(TEXT("CSV Settings"), TEXT("Include Headers"), mHeadersInCsv);
	iniFile->WriteBool(TEXT("CSV Settings"), TEXT("Simulator Active"), mSimulatorActive);

	iniFile->WriteBool(TEXT("Main Settings"), TEXT("Version2023"), mVersion2023);
}

