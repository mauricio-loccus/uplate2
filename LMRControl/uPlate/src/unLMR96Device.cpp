//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.DateUtils.hpp>
#include <System.RegularExpressions.hpp>
#include <System.SyncObjs.hpp>
#include <SetupApi.h>

#include <sstream>
#include <iostream>
#include <limits>
#include <iomanip>

#include <boost/algorithm/string.hpp>

#pragma hdrstop

#include "unLMR96Device.h"

#include "crcfast.h"
#include "unStrUtils.h"
#include "unFileFilters.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

const Byte COMMAND_PLATE_OUT = 0x08;
const Byte COMMAND_PLATE_IN  = 0x09;

const Byte STX = 0x02;
const Byte ETX = 0x03;
const Byte ACK = 0x06;

const Word ElisaVendorID = 0x04E2;
const Word ElisaProductID = 0x1410;

__fastcall LMR96SerialPortThread::LMR96SerialPortThread(TLMR96Device *_owner, TZylSerialPort *serial, const ByteArray& cmd)
			: TThread(True), owner(_owner), device(serial), cmdString(cmd)
{
}

NativeInt __fastcall LMR96SerialPortThread::GetExitStatus()
{
	return exitStatus;
}

void __fastcall LMR96SerialPortThread::SetExitStatus(NativeInt status)
{
	exitStatus = status;
}

void __fastcall LMR96SerialPortThread::Execute()
{
	using System::Syncobjs::TWaitResult;

	owner->SerialThreadMutex->Acquire();

	if (!device->SendData((System::Pointer)cmdString.data(), cmdString.size()))
	{
		SetExitStatus(-1);
		owner->SerialThreadMutex->Release();

		return;
	}

	owner->commandStatus = ElisaDeviceCommandStatus::ElisaDeviceCommand_Sended;

	TWaitResult waitResult = owner->SerialThreadEvent->WaitFor(INFINITE);
	owner->SerialThreadEvent->ResetEvent();

	owner->SerialThreadMutex->Release();

	owner->commandStatus = ElisaDeviceCommandStatus::ElisaDeviceCommand_Idle;
}

__fastcall TLMR96Device::TLMR96Device(TComponent *owner) : TElisaDevice(owner)
{
	// carrega os filtros do arquivo filters.ini
	mpFilters = FileFiltersSingleton::instance();

	// Ler filtros do arquivo
	strcpy (m_Filters.filter[0], "");
	strcpy (m_Filters.filter[1], "");
	strcpy (m_Filters.filter[2], "");
	strcpy (m_Filters.filter[3], "");
	strcpy (m_Filters.filter[4], "");
	strcpy (m_Filters.filter[5], "");
	strcpy (m_Filters.filter[6], "");
	strcpy (m_Filters.filter[7], "");
	TStringList *filt  = new TStringList();
	mpFilters->getFilters (filt);
	for (int i = 0; i < filt->Count; i++) {
		AnsiString str = filt->Strings[i] + " nm";
		strncpy(m_Filters.filter[i], str.c_str(), 10);
	}

//	bufferSerial.resize(2000);
//	idxBufferFim = 0;
//	idxBufferIni = 0;

	MyDataModule->ZylSerialPort->AutoReceive = False;
	MyDataModule->ZylSerialPort->NewLine = "\n";
	MyDataModule->ZylSerialPort->BaudRate = TBaudRate::br115200;
	MyDataModule->ZylSerialPort->OnReceive = TLMR96Device::OnReceive;
	MyDataModule->ZylSerialPort->OnFault = TLMR96Device::OnFault;

	SerialThreadEvent = new TEvent(False);
	SerialThreadMutex = new TMutex(False);

	mDeviceType = ElisaDeviceTypeEnum::ElisaDeviceLMR96;
}

__fastcall TLMR96Device::~TLMR96Device()
{
	if (SerialThreadEvent)
    {
        SerialThreadEvent->Free();
        SerialThreadEvent = NULL;
    }

    if (SerialThreadMutex)
    {
        SerialThreadMutex->Free();
        SerialThreadMutex = NULL;
    }

	if (MyDataModule->ZylSerialPort->IsConnected())
		MyDataModule->ZylSerialPort->Close();
}

Boolean __fastcall TLMR96Device::Connect(AnsiString commName)
{
	MyDataModule->ZylSerialPort->Port = MyDataModule->ZylSerialPort->StringToCommPort(commName);
	MyDataModule->ZylSerialPort->Open();

	sendGetKey();

	if (!authenticated)
	   return False;

	sendConnectCommand();

	return isConnected;
}

void __fastcall TLMR96Device::Disconnect()
{
	sendDisconnectCommand();
	MyDataModule->ZylSerialPort->Close();
}

void __fastcall TLMR96Device::Terminate()
{
	SerialThreadEvent->SetEvent();

	if (MyDataModule->ZylSerialPort->IsConnected())
		MyDataModule->ZylSerialPort->Close();

	lastErrorCode = -1;
}

void __fastcall TLMR96Device::sendDoorCommand(Boolean openClose)
{
	currCommand = ElisaCommands::ElisaCommand_OpenDoor;

	if (!openClose)
		currCommand = ElisaCommands::ElisaCommand_CloseDoor;

	OByteArrayStream os;

	os << STX << ByteArray("70")
	   << std::setw(2) << std::right << std::setfill('0')
	   << loccus::ToByteArray((Word)currCommand) << std::setw(1) << ETX;

	ByteArray segment = os.str();

	CRCFast cf;

	Word crcValue = cf.calculate(segment);
	Word crcValue2 = crcFast((LPBYTE)segment.data(), segment.length());

	os << std::setw(4) << std::right << std::setfill('0') << std::hex << crcValue << ByteArray("\r\n");

	ByteArray packet = os.str();
	SendCommand(packet);
}

void __fastcall TLMR96Device::sendConnectCommand()
{
	currCommand = ElisaCommands::ElisaCommand_OpenConnection;

	OByteArrayStream os;

	os << STX << ByteArray("70")
	   << std::setw(2) << std::right << std::setfill('0')
	   << loccus::ToByteArray((Word)currCommand) << std::setw(1) << ETX;

	ByteArray segment = os.str();
	CRCFast cf;
	Word crcValue = cf.calculate(segment);
	Word crcValue2 = crcFast((LPBYTE)segment.data(), segment.length());

	os << std::setw(4) << std::right << std::setfill('0') << std::hex << crcValue << ByteArray("\r\n");

	ByteArray packet = os.str();
	SendCommand(packet);
}

void __fastcall TLMR96Device::sendDisconnectCommand()
{
	currCommand = ElisaCommands::ElisaCommand_CloseConnection;

	OByteArrayStream os;

	os << STX << ByteArray("70")
	   << std::setw(2) << std::right << std::setfill('0')
	   << loccus::ToByteArray((Word)currCommand) << std::setw(1) << ETX;

	ByteArray segment = os.str();
	CRCFast crcFast;
	uint16_t crcValue = crcFast.calculate(segment);

	os << std::setw(4) << std::right << std::setfill('0') << std::hex << crcValue << ByteArray("\r\n");

	ByteArray packet = os.str();
	SendCommand(packet);
}

void __fastcall TLMR96Device::sendRunProgram()
{
	currCommand = ElisaCommands::ElisaCommand_RunProgram;

	Word hh = HourOf(params->ShakeDuration);
	Word mm = MinuteOf(params->ShakeDuration);
	Word ss = SecondOf(params->ShakeDuration);
	Word filter1Num = params->Filter1+1;
	Word filter2Num = params->Filter2+1;
	Word hasShake   = params->Shake? 1: 0;
	Word shakeIntensity = params->ShakeIntensity;
	Word calcMethod = params->CalcMethod;

	OByteArrayStream os;

	os << STX << ByteArray("70")
	   << std::setw(2) << std::right << std::setfill('0')
	   << loccus::ToByteArray((Word)currCommand)
	   << std::setw(2) << std::right << std::setfill('0') << std::hex << filter1Num
	   << std::setw(2) << std::right << std::setfill('0') << std::hex << filter2Num
	   << std::setw(2) << std::right << std::setfill('0') << std::hex << calcMethod
	   << std::setw(2) << std::right << std::setfill('0') << std::hex << hasShake
	   << std::setw(2) << std::right << std::setfill('0') << std::hex << shakeIntensity
	   << std::setw(2) << std::right << std::setfill('0') << std::hex << hh
	   << std::setw(2) << std::right << std::setfill('0') << std::hex << mm
	   << std::setw(2) << std::right << std::setfill('0') << std::hex << ss
	   << ETX;

	ByteArray segment = os.str();
	CRCFast crcFast;
	uint16_t crcValue = crcFast.calculate(segment);

	os << std::setw(4) << std::right << std::setfill('0') << std::hex << crcValue << ByteArray("\r\n");

	ByteArray packet = os.str();

	SendCommand(packet);
}

void __fastcall TLMR96Device::sendGetCapabilitiesCommand()
{
	currCommand = ElisaCommands::ElisaCommand_RunProgram;

	OByteArrayStream os;
	os << STX << ByteArray("70")
	   << std::setw(2) << std::right << std::setfill('0')
	   << loccus::ToByteArray((Word)currCommand) << std::setw(1) << ETX;

	ByteArray segment = os.str();
	CRCFast crcFast;
	Word crcValue = crcFast.calculate(segment);

	os << std::setw(4) << std::setfill('0') << std::hex << crcValue << "\r\n";

	ByteArray packet = os.str();
	SendCommand(packet);
}

void __fastcall TLMR96Device::sendGetFilterList()
{
	currCommand = ElisaCommands::ElisaCommand_GetFiltersList;

	OByteArrayStream os;
	os << STX << ByteArray("70")
	   << std::setw(2) << std::right << std::setfill('0')
	   << loccus::ToByteArray((Word)currCommand) << std::setw(1) << ETX;

	ByteArray segment = os.str();
	CRCFast crcFast;
	Word crcValue = crcFast.calculate(segment);

	os << std::setw(4) << std::setfill('0') << std::hex << crcValue << "\r\n";

	ByteArray packet = os.str();
	SendCommand(packet);
}

void __fastcall TLMR96Device::sendSetFilterList()
{
	currCommand = ElisaCommands::ElisaCommand_SetFiltersList;

	ByteArray outBuffer;
	OByteArrayStream os(outBuffer, OByteArrayStream::out|OByteArrayStream::binary);
	os << STX << ByteArray("70")
	   << std::setw(2) << std::right << std::setfill('0')
	   << loccus::ToByteArray((Word)currCommand) << m_Filters << std::setw(1) << ETX;

	ByteArray segment = os.str();
	CRCFast crcFast;
	Word crcValue = crcFast.calculate(segment);

	os << std::setw(4) << std::setfill('0') << std::hex << crcValue << "\r\n";

	ByteArray packet = os.str();
	SendCommand(packet);
}

Boolean __fastcall TLMR96Device::sendGetKey()
{
	currCommand = ElisaCommands::ElisaCommand_GetKey;

	OByteArrayStream os;
	os << STX << ByteArray("70")
	   << std::setw(2) << std::right << std::setfill('0')
	   << loccus::ToByteArray((Word)currCommand) << std::setw(1) << ETX;

	ByteArray segment = os.str();
	CRCFast crcFast;
	Word crcValue = crcFast.calculate(segment);

	os << std::setw(4) << std::setfill('0') << std::hex << crcValue << "\r\n";

	ByteArray packet = os.str();

	SendCommand(packet);

	return True;
}

void __fastcall TLMR96Device::sendGetStatus()
{
	currCommand = ElisaCommands::ElisaCommand_GetStatus;

	OByteArrayStream os;
	os << STX << ByteArray("70")
	   << std::setw(2) << std::right << std::setfill('0')
	   << loccus::ToByteArray((Word)currCommand) << std::setw(1) << ETX;

	ByteArray segment = os.str();
	CRCFast crcFast;
	Word crcValue = crcFast.calculate(segment);

	os << std::setw(4) << std::setfill('0') << std::hex << crcValue << "\r\n";

	ByteArray packet = os.str();

	SendCommand(packet);
}

void __fastcall TLMR96Device::OnReceive(TObject *Sender, AnsiString Buffer)
{
	using System::Sysutils::Format;

	Buffer = MyDataModule->ZylSerialPort->ReadStringUpToEndChars("\r\n");

	Integer bufferLen = Buffer.Length();

	ByteArray data;

	for (Integer i = 0; i < bufferLen; i++)
		data.push_back(Buffer[i+1]);

	ByteArray::size_type posETX = data.rfind(ETX);
	if (ByteArray::npos == posETX)
	{
		SerialThreadEvent->SetEvent();

		TaskMessageDlg(TEXT("Atenção"),
					   TEXT("Erro durante a comunicação com a LMR96.\n"
							"Reinicie o programa com o equipamento ligado e tente novamente."),
					   mtError,
					   TMsgDlgButtons() << mbOK, 0);
		lastErrorCode = -1;
		return;
	}

	ByteArray crcString = data.substr(posETX+1, 4);
	uint16_t crcValue = loccus::FromByteArray<uint16_t>(crcString, std::hex);

	ByteArray segment = data.substr(0, posETX+1);

	CRCFast crcFast;
	Word crcCalc = crcFast.calculate(segment);

	if (crcValue != crcCalc)
	{
		SerialThreadEvent->SetEvent();

		TaskMessageDlg(TEXT("Atenção"),
					   TEXT("Erro durante a comunicação com a LMR96.\n"
							"Reinicie o programa com o equipamento ligado e tente novamente."),
					   mtError,
					   TMsgDlgButtons() << mbOK, 0);
		lastErrorCode = -1;
		return;
	}

	IByteArrayStream is(segment);

	Byte stx;
	ByteArray cmd(4, 0);
	Byte status;

	is >> stx >> std::setw(4) >> cmd >> std::setw(1) >> status;

	if (status == 0)
	{
		Word errCode = 0;

		is.read((LPSTR)&errCode, sizeof(errCode));
		ByteArray errMsg = is.str().substr(8, (posETX-1)-8);

		SerialThreadEvent->SetEvent();

		MessageDlg(Format(_T("Error %d: %s"), ARRAYOFCONST((errCode, errMsg.c_str()))),
				   mtError, TMsgDlgButtons() << mbOK, 0);

		lastErrorCode = -1;
		return;
	}

	Word receivedCmd = loccus::FromByteArray<Word>(cmd.substr(2));

	commandStatus = ElisaDeviceCommandStatus::ElisaDeviceCommand_Received;

	switch (receivedCmd)
	{
		case ElisaCommands::ElisaCommand_OpenDoor:
			doorStatus = True;
			break;

		case ElisaCommands::ElisaCommand_CloseDoor:
			doorStatus = False;
			break;

		case ElisaCommands::ElisaCommand_GetDefaultValue:
			is >> board_inf;
			break;

		case ElisaCommands::ElisaCommand_OpenConnection:
		case ElisaCommands::ElisaCommand_CloseConnection:
		case ElisaCommands::ElisaCommand_SetFiltersList:
			break;

		case ElisaCommands::ElisaCommand_GetFiltersList:
		{
			IByteArrayStream ii(segment.substr(6, posETX-6));
			ii >> m_Filters;

			size_t filtersCount = 0;
			for (size_t i = 0; i < FILTER_MAX; i++)
			{
				AnsiString filterName = AnsiString(m_Filters.filter[i]).UpperCase();

				if (filterName.IsEmpty() ||
					filterName == "OFF"  ||
					filterName == "NO")
					continue;

					filtersCount++;
			}

			mDeviceType = ElisaDeviceTypeEnum::ElisaDeviceLMR96;

			if (!filtersCount)
				mDeviceType = ElisaDeviceTypeEnum::ElisaDeviceLMR96Flex;

			break;
		}

		case ElisaCommands::ElisaCommand_RunProgram:
		{
			RawDataMatrix::size_type idx;
			for (RawDataMatrix::size_type row = 0, idx; row < rawData.size(); row++)
			{
				for (ColumnsData::size_type col = 0; col < rawData[row].size(); col++, idx++)
				{
					Double value(0);

					is.read((LPSTR)&value, sizeof(Double));

					if (is.fail())
					{
						SerialThreadEvent->SetEvent();

						MessageDlg(Format(_T("Unable to read data received at position %d."), ARRAYOFCONST((idx))),
								   mtError, TMsgDlgButtons() << mbOK, 0);

						return;
					}

					rawData[row][col] = value;
				}
			}

			if (IsReadEventStored())
				onReadEvent(this, rawData, rawData);

			break;
		}

		case ElisaCommands::ElisaCommand_StopExecution:
			break;

		case ElisaCommands::ElisaCommand_GetKey:
		{
			ByteArray hashKey;

			is >> std::setw(ElisaHashKeyLength) >> hashKey;

			if (hashKey == ElisaHashKey)
				authenticated = True;

			break;
		}

		case ElisaCommands::ElisaCommand_GetStatus:
		{
			RUN_STATUS run_status;

			is >> run_status;

			runStatus = static_cast<ElisaDeviceRunModeStatus>(run_status.nRunMode);
		}
	}

	SerialThreadEvent->SetEvent();
}

Integer __fastcall TLMR96Device::SendCommand(const ByteArray& cmd, bool waitResponse)
{
	lastErrorCode = 0;

	LMR96SerialPortThread *thSerial = new LMR96SerialPortThread(this, MyDataModule->ZylSerialPort, cmd);
	thSerial->Suspended = False;

	while (!thSerial->Finished)
		Application->ProcessMessages();

	NativeUInt wReturn = thSerial->WaitFor();

	isFaulted = (thSerial->ExitStatus != 0);
	if (isFaulted)
		throw Exception(TEXT("Perda de comunicação com equipamento."));

	thSerial->Free();
    thSerial = NULL;

	return wReturn;
}

void __fastcall TLMR96Device::OnFault(TObject *Sender, TCommPort Port)
{
	using System::Sysutils::Format;

	MessageDlg(Format("Fatal error on port \"%s\"", ARRAYOFCONST((MyDataModule->ZylSerialPort->CommPortToString(Port)))),
			   mtError, TMsgDlgButtons() << mbOK, 0);

	SerialThreadMutex->Release();
	isFaulted = LastErrorCode;
}


StlStringList __fastcall TLMR96Device::GetPortNames()
{
	StlStringList names;

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
		return names;
	}

	hdevInfo = SetupDiGetClassDevs(&guid[0], NULL, NULL, DIGCF_PRESENT|DIGCF_PROFILE);

	if (hdevInfo == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Error: SetupDiGetClassDevs() failed." << std::endl;
		return names;
	}

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

		names.push_back(portName);
	}

	SetupDiDestroyDeviceInfoList(hdevInfo);

	StlStringList rightPorts;

	for (StlStringList::const_iterator cit = names.begin(); cit != names.end(); ++cit)
	{
		StlString hwdID = GetHardwareID(*cit);
		StlString serial = parseDeviceSerialNumber(hwdID);

		Boolean hasVendorID = False, hasProductID = False;

		Word vendorID = deviceVendorIdentifier(hwdID, hasVendorID);

		if (!hasVendorID || ElisaVendorID != vendorID)
			continue;

		Word productID = deviceProductIdentifier(hwdID, hasProductID);

		if (!hasProductID || ElisaProductID != productID)
			continue;

		rightPorts.push_back(*cit);
	}

	return rightPorts;
}

