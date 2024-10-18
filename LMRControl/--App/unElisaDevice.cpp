//---------------------------------------------------------------------------
#include <vcl.h>

#include <sstream>
#include <iostream>
#include <limits>
#include <iomanip>
#include <SetupApi.h>

#include <boost/algorithm/string.hpp>

#pragma hdrstop

#include "unElisaDevice.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

const LPCSTR ElisaHashKey = "FE5725B2F7E25D5B8657969E6D263C1D6ABBD16D176F7C2461A2254B61A5FF19";
const Word ElisaHashKeyLength = 64;

const StlString GetHardwareID(const StlString& commName)
{
	BOOL rv = FALSE;
	DWORD size = 0;
	GUID guid[1];
	HDEVINFO hdevInfo = INVALID_HANDLE_VALUE;

	SP_DEVINFO_DATA devInfoData;
	devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	DWORD idx = 0;

	rv = SetupDiClassGuidsFromName(_T("Ports"), (LPGUID)&guid, 1, &size);

	if (!rv)
	{
		std::cerr << "Error: SetupDiClassGuidsFromName() failed." << std::endl;
		return StlString();
	}

	hdevInfo = SetupDiGetClassDevs(&guid[0], NULL, NULL, DIGCF_PRESENT|DIGCF_PROFILE);

	if (hdevInfo == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Error: SetupDiGetClassDevs() failed." << std::endl;
		return StlString();
	}

	StlString sHardwareID;

	while (SetupDiEnumDeviceInfo(hdevInfo, idx++, &devInfoData))
	{
		TCHAR friendlyName[MAX_PATH] = _T("");
		TCHAR portName[MAX_PATH] = _T("");

		DWORD propType;
		DWORD type = REG_SZ;
		HKEY hKey = NULL;

		rv = SetupDiGetDeviceRegistryProperty(hdevInfo,
											  &devInfoData,
											  SPDRP_FRIENDLYNAME,
											  &propType,
											  (LPBYTE)friendlyName,
											  sizeof(friendlyName),
											  &size);

		if (!rv)
		{
			std::cerr << "Error: SetupDiGetDeviceRegistryProperty() failed." << std::endl;
			continue;
		}

		hKey = SetupDiOpenDevRegKey(hdevInfo, &devInfoData, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_READ);
		if (!hKey)
			continue;

		rv = RegQueryValueEx(hKey, _T("PortName"), 0, &type, (LPBYTE)&portName, &size);

		RegCloseKey(hKey);

		if (StlString(portName) != commName)
			continue;

		TCHAR hardwareID[MAX_PATH] = _T("");
		type = REG_MULTI_SZ;

		rv = SetupDiGetDeviceRegistryProperty(hdevInfo,
											  &devInfoData,
											  SPDRP_HARDWAREID,
											  &propType,
											  (LPBYTE)&hardwareID,
											  sizeof(hardwareID),
											  &size);

		if (!rv)
		{
			std::cerr << "Error: SetupDiGetDeviceRegistryProperty() failed." << std::endl;
			return StlString();
		}

		sHardwareID = (LPCTSTR)hardwareID;
		break;
	}

	SetupDiDestroyDeviceInfoList(hdevInfo);

	return sHardwareID;
}

Word parseDeviceIdentifier(const StlString& instanceIdentifier,
						   const StlString& instancePrefix,
						   Integer identifierSize, Boolean& ok)
{
	const StlString::size_type index = instanceIdentifier.rfind(instancePrefix);

	if (index == StlString::npos)
	{
		ok = False;
		return 0;
	}

	StlString inHex = instanceIdentifier.substr(index + instancePrefix.length(), identifierSize);

	Word value = 0;

	ok = loccus::FromString(value, inHex, std::hex);

	return value;
}

Word deviceVendorIdentifier(const StlString& instanceIdentifier, bool &ok)
{
	static const Word vendorIdentifierSize = 4;

	Word result = parseDeviceIdentifier(instanceIdentifier, _T("VID_"), vendorIdentifierSize, ok);

	if (!ok)
		result = parseDeviceIdentifier(instanceIdentifier, _T("VEN_"), vendorIdentifierSize, ok);

	return result;
}

Word deviceProductIdentifier(const StlString& instanceIdentifier, bool &ok)
{
	static const Word productIdentifierSize = 4;

	Word result = parseDeviceIdentifier(instanceIdentifier, _T("PID_"), productIdentifierSize, ok);

	if (!ok)
		result = parseDeviceIdentifier(instanceIdentifier, _T("DEV_"), productIdentifierSize, ok);

	return result;
}

StlString parseDeviceSerialNumber(const StlString& instanceIdentifier)
{
	StlString::size_type firstBound = instanceIdentifier.find_last_of('\\');
	StlString::size_type lastBound  = instanceIdentifier.find_last_of('_', firstBound);

	if (instanceIdentifier.find_first_of(_T("USB\\")) == 0)
	{
		if (lastBound != instanceIdentifier.length()-3)
			lastBound = instanceIdentifier.length();

		StlString::size_type ampersand = instanceIdentifier.find_first_of('&', firstBound);

		if (ampersand != StlString::npos && ampersand < lastBound)
			return StlString();
	}
	else
	{
		if (boost::starts_with(instanceIdentifier, _T("FTDIBUS\\")))
		{
			firstBound = instanceIdentifier.find_last_of('+');
			lastBound = instanceIdentifier.find_first_of('\\', firstBound);

			if (StlString::npos == lastBound)
				return StlString();
		}
		else
			return StlString();
	}

	return instanceIdentifier.substr(firstBound+1, lastBound-firstBound-1);
}

__fastcall TElisaDevice::TElisaDevice(TComponent *owner) : TObject(),
		   mParent(owner),
		   runStatus(ElisaDeviceRunModeStatus::ElisaDeviceRunMode_IDLE),
		   lastErrorCode(0), authenticated(False), onReadEvent(NULL),
		   onAboutToStartEvent(NULL), onAboutToFinishEvent(NULL), onCommunicationTimeoutEvent(NULL),
		   commandStatus(ElisaDeviceCommandStatus::ElisaDeviceCommand_Idle) {}

