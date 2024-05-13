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

#include "unLMR962023Device.h"

#include "crcfast.h"
#include "unStrUtils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)




////////////////////////////////////////////////////////////////////////////////
__fastcall LMR962023SerialPortThread::LMR962023SerialPortThread(TLMR962023Device *_owner,
			TZylSerialPort *serial, const ByteArray& cmd, bool _waitResponse)
			: TThread(True), owner(_owner), device(serial), cmdString(cmd), waitResponse(_waitResponse)
{
}

NativeInt __fastcall LMR962023SerialPortThread::GetExitStatus()
{
	return exitStatus;
}

void __fastcall LMR962023SerialPortThread::SetExitStatus(NativeInt status)
{
	exitStatus = status;
}

void __fastcall LMR962023SerialPortThread::Execute()
{
	using System::Syncobjs::TWaitResult;

	owner->SerialThreadMutex->Acquire();
	int size = cmdString.size();
	int res = device->SendData((System::Pointer)cmdString.data(), size);
	if (res < 0)
	{
		SetExitStatus(-1);
		owner->SerialThreadMutex->Release();

		return;
	}

	owner->commandStatus = ElisaDeviceCommandStatus::ElisaDeviceCommand_Sended;

	if(waitResponse)
  		TWaitResult waitResult = owner->SerialThreadEvent->WaitFor(INFINITE);

	owner->SerialThreadEvent->ResetEvent();

	owner->SerialThreadMutex->Release();

	owner->commandStatus = ElisaDeviceCommandStatus::ElisaDeviceCommand_Idle;
}

//////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
__fastcall TLMR962023Device::TLMR962023Device(TComponent *owner) : TElisaDevice(owner)
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
 //	strcpy ((unsigned char *)&(m_Filters.filter[0]), "405 nm");
 //	strcpy ((unsigned char *)&(m_Filters.filter[1]), "450 nm");
 //	strcpy ((unsigned char *)&(m_Filters.filter[2]), "492 nm");
 //	strcpy ((unsigned char *)&(m_Filters.filter[3]), "630 nm");

	bufferSerial.resize(2000);
	idxBufferFim = 0;
	idxBufferIni = 0;

	MyDataModule->ZylSerialPort->AutoReceive = False;
	MyDataModule->ZylSerialPort->NewLine = "\n";
	MyDataModule->ZylSerialPort->BaudRate = TBaudRate::br115200;
	MyDataModule->ZylSerialPort->OnReceive = TLMR962023Device::OnReceive;
	MyDataModule->ZylSerialPort->OnFault = TLMR962023Device::OnFault;

	SerialThreadEvent = new TEvent(False);
	SerialThreadMutex = new TMutex(False);

	mDeviceType = ElisaDeviceTypeEnum::ElisaDeviceLMR96;
}

__fastcall TLMR962023Device::~TLMR962023Device()
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

Boolean __fastcall TLMR962023Device::Connect(AnsiString commName)
{
	MyDataModule->ZylSerialPort->Port = MyDataModule->ZylSerialPort->StringToCommPort(commName);
	MyDataModule->ZylSerialPort->Close();
	MyDataModule->ZylSerialPort->Open();
	MyDataModule->ZylSerialPort->ClearInputBuffer();
	MyDataModule->ZylSerialPort->ClearOutputBuffer();

   //	sendGetKey();
  //	if (!authenticated)
  //	   return False;

	// Pra nao travar a comuniccao, tem que enviar um disconect primeiro, e depois um connect
	sendDisconnectCommand();
  	Sleep(100);
	sendConnectCommand();
	authenticated = true;

	return isConnected;
}

void __fastcall TLMR962023Device::Disconnect()
{
	sendDisconnectCommand();
	MyDataModule->ZylSerialPort->Close();
}

void __fastcall TLMR962023Device::Terminate()
{
	SerialThreadEvent->SetEvent();

	if (MyDataModule->ZylSerialPort->IsConnected())
		MyDataModule->ZylSerialPort->Close();

	lastErrorCode = -1;
}


ByteArray TLMR962023Device::checksum(ByteArray array)
{
	ByteArray CRC;
	CRC.resize(2);
	unsigned short sum = 0;
	for(int i=0; i < array.size(); i++){
		sum += static_cast<unsigned char>(array[i]);
	}
	CRC[0] = sum>>8;
	CRC[1] = sum&0xFF;
	return CRC;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Commands
void __fastcall TLMR962023Device::sendDoorCommand(Boolean openClose)
{
	currCommand = ElisaCommands::ElisaCommand_OpenDoor;

	if (!openClose)
		currCommand = ElisaCommands::ElisaCommand_CloseDoor;
	ByteArray packet = ByteArray("\xFA\xFB\xFC\xFD");

	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x70);
	packet.push_back(0x00);

	packet.push_back(0x00);
	if (openClose)
		packet.push_back(0x06);     // COMMAND_PLATEOUT
	else
		packet.push_back(0x05);     //COMMAND_PLATEIN

	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x02);

	ByteArray CS = checksum(packet);
	packet.push_back(CS[0]);
	packet.push_back(CS[1]);

	SendCommand(packet, true);
}

void __fastcall TLMR962023Device::sendConnectCommand()
{
	currCommand = ElisaCommands::ElisaCommand_OpenConnection;

	ByteArray packet = ByteArray("\xFA\xFB\xFC\xFD");
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x70);
	packet.push_back(0x00);

	packet.push_back(0x00);
	packet.push_back(0x01);        // COMMAND_CONNECT

	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x02);

	ByteArray CS = checksum(packet);
	packet.push_back(CS[0]);
	packet.push_back(CS[1]);

	SendCommand(packet, true);
}

void __fastcall TLMR962023Device::sendDisconnectCommand()
{
	currCommand = ElisaCommands::ElisaCommand_CloseConnection;

	OByteArrayStream os;

	ByteArray packet = ByteArray("\xFA\xFB\xFC\xFD");
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x70);
	packet.push_back(0x00);

	packet.push_back(0x00);
	packet.push_back(0x02);    // COMMAND_UNCONNECT

	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x02);

	ByteArray CS = checksum(packet);
	packet.push_back(CS[0]);
	packet.push_back(CS[1]);

	SendCommand(packet);
}

void __fastcall TLMR962023Device::sendSetParams()
{
//	currCommand = ElisaCommands::ElisaCommand_RunProgram;

	unsigned char filter1Num = params->Filter1+1;
	unsigned char filter2Num = params->Filter2+1;
	unsigned char speedRead   = params->ReadSpeed;  // 1 = standard; 0 = Fast  - pelo que medi da o contrario...
	unsigned char hasShake   = params->Shake? 1: 0;
	unsigned char shakeIntensity = params->Shake? params->ShakeIntensity: 0;  // 1=low, 2=medium, 3=high
	unsigned char shakeMode = params->ShakeMode;       // SHAKE_FIRST =0 ou SHAKE_EACH=1

	Word hh = HourOf(params->ShakeDuration);
	Word mm = MinuteOf(params->ShakeDuration);
	Word ss = SecondOf(params->ShakeDuration);
	DWord shakeDuration = (hh*60*60) + (mm*60) + ss;

	hh = HourOf(params->WaitDuration);
	mm = MinuteOf(params->WaitDuration);
	ss = SecondOf(params->WaitDuration);
	DWord waitDuration = (hh*60*60) + (mm*60) + ss;

	////////////////////////////////////////////////////////
	// 53 bytes
	ByteArray packet = ByteArray("\xFA\xFB\xFC\xFD");
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x70);
	packet.push_back(0x00);

	packet.push_back(0x00);
	packet.push_back(0x08);   // COMMAND_MEASURE_PARAM

	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x23);     // qtd bytes

	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x01);       // constante - PlateCurrent, eu acho

	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(filter1Num);//0x01);//filter1Num); //

	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(filter2Num);//0x00);//3);  // filter2

	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(speedRead);//0x00);  // speed_Read   - 1 = standard; 0 = Fast

	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(hasShake);//(0x00);     // // enable shake   (0 ou 1 acho)

	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(shakeIntensity);//0x00);     //velocidade shake - 1=low, 2=medium, 3=high

	packet.push_back((shakeDuration&0xFF000000)>>24);//0x00);
	packet.push_back((shakeDuration&0x00FF0000)>>16);//0x00);
	packet.push_back((shakeDuration&0x0000FF00)>>8);//0x00);
	packet.push_back((shakeDuration&0x000000FF));//0x01);   // tempo de shake em segundos (4 bytes big endian)

	packet.push_back(shakeMode);//0x00);   // ShakeMode=SHAKE_FIRST =0 ou SHAKE_EACH=1

	packet.push_back((waitDuration&0xFF000000)>>24);// 0x00);
	packet.push_back((waitDuration&0x00FF0000)>>16);//0x00);
	packet.push_back((waitDuration&0x0000FF00)>>8);//0x00);
	packet.push_back((waitDuration&0x000000FF));//0x00);    // tempo de espera em segundos (4 bytes big endian)

	ByteArray CS = checksum(packet);
	packet.push_back(CS[0]);
	packet.push_back(CS[1]);

	SendCommand(packet);
}

//////////
void __fastcall TLMR962023Device::sendRunProgram()
{
	///////////////////
	// Init program

	ByteArray packet2 = ByteArray("\xFA\xFB\xFC\xFD");
	packet2.push_back(0x00);
	packet2.push_back(0x00);
	packet2.push_back(0x00);
	packet2.push_back(0x00);
	packet2.push_back(0x00);
	packet2.push_back(0x00);
	packet2.push_back(0x00);
	packet2.push_back(0x00);
	packet2.push_back(0x70);
	packet2.push_back(0x00);

	packet2.push_back(0x00);
	packet2.push_back(0x03);   // COMMAND_RUN

	packet2.push_back(0x00);
	packet2.push_back(0x00);
	packet2.push_back(0x00);
	packet2.push_back(0x06);

	packet2.push_back(0x00);
	packet2.push_back(0x00);
	packet2.push_back(0x00);
	packet2.push_back(0x01);//00 no word doc

	ByteArray CS2 = checksum(packet2);
	packet2.push_back(CS2[0]);
	packet2.push_back(CS2[1]);

	SendCommand(packet2, true);

}

void __fastcall TLMR962023Device::sendGetCapabilitiesCommand()
{
  //	currCommand = ElisaCommands::ElisaCommand_RunProgram;
/*
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
*/
}

void __fastcall TLMR962023Device::sendGetFilterList()
{
 //	currCommand = ElisaCommands::ElisaCommand_GetFiltersList;
/*
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
*/
}

void __fastcall TLMR962023Device::sendSetFilterList()
{
  //	currCommand = ElisaCommands::ElisaCommand_SetFiltersList;
/*
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
*/
}

void __fastcall TLMR962023Device::sendGetStatus()
{
	//currCommand = ElisaCommands::ElisaCommand_GetStatus;
 /*
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
*/
}

int TLMR962023Device::findHeader(ByteArray arr, int posIni, int posFim)
{
	unsigned idx = posIni;
	while (idx+3 < posFim){
		unsigned char d1 = arr[idx];
		unsigned char d2 = arr[idx+1];
		unsigned char d3 = arr[idx+2];
		unsigned char d4 = arr[idx+3];
		if (d1 == 0xFA &&
			d2 == 0xFB &&
			d3 == 0xFC &&
			d4 == 0xFD)
		{
			return idx;
		}
		idx++;
	}

	return -1;
}

////////////////////////////////////////////////////////////////////////////////
// On receive dadods da serial
void __fastcall TLMR962023Device::OnReceive(TObject *Sender, AnsiString Buffer)
{
	using System::Sysutils::Format;

	// Le o buffer todo
	Integer bufferLen = MyDataModule->ZylSerialPort->GetBufferSize();
	if (bufferLen < 20){
        // se for menor que 20 (1 comando inteiro), nao processa o buffer
		return;
	}

   //	ByteArray data;
	for (Integer i = 0; i < bufferLen; i++) {
		unsigned char byteRec = MyDataModule->ZylSerialPort->ReadByte();
		//data.push_back(byteRec);
		bufferSerial[idxBufferFim++] = byteRec;
	}

	///////////////////////////////////////////////////////////
	do {

		// Procura o header
	   //	ByteArray::size_type posH = data.rfind("\xFA\xFB\xFC\xFD");
		unsigned int posH = findHeader(bufferSerial, idxBufferIni, idxBufferFim);
		if (posH < 0 || (idxBufferFim-posH) < 20) {  //  ve se achou o header e recebeu um header inteiro
			// erro
			//lastErrorCode = -1;
			SerialThreadEvent->SetEvent();      // pra destravar a thread execute (sendCommand/execute)
			return;
		}
		idxBufferIni = posH;

		// Checa qtd bytes do pacote
		unsigned int qtdBytes = 0;
		qtdBytes  = ((unsigned char)bufferSerial[idxBufferIni+19]);
		qtdBytes |= ((unsigned char)bufferSerial[idxBufferIni+18])<<8;
		qtdBytes |= ((unsigned char)bufferSerial[idxBufferIni+17])<<16;
		qtdBytes |= ((unsigned char)bufferSerial[idxBufferIni+16])<<24;

		if ((idxBufferFim-idxBufferIni) < 20+qtdBytes) {    // checa se precisa ler mais bytes pra completar um pacote
			// erro
			//lastErrorCode = -1;
//			SerialThreadEvent->SetEvent();      // pra destravar a thread execute (sendCommand/execute)
			return;
		}

		//////////////////////////////////////////////////////////////////////
		// Copia comando recebido
		ByteArray receivedData;
		receivedData.resize(20+qtdBytes-2);
		for (int c = 0; c < 20+qtdBytes-2; c++)
		   receivedData[c] = bufferSerial[idxBufferIni+c];
		idxBufferIni += 20+qtdBytes-2;
		ByteArray receivedCRC;
		receivedCRC.push_back(bufferSerial[idxBufferIni++]);
		receivedCRC.push_back(bufferSerial[idxBufferIni++]);

		// Calcula CRC e verifica
		ByteArray CS = checksum(receivedData);
		unsigned char c1 = CS[0];
		unsigned char c2 = CS[1];
		unsigned char r1 = receivedCRC[0];
		unsigned char r2 = receivedCRC[1];
		if (CS[0] != receivedCRC[0] || CS[1] != receivedCRC[1]) {
			// erro Checksum
			//lastErrorCode = -2;
			SerialThreadEvent->SetEvent();      // pra destravar a thread execute (sendCommand/execute)
			continue;//return;
		}

		//////////////////////////////////////////////////////////////////////
		// trata recebimento
		commandStatus = ElisaDeviceCommandStatus::ElisaDeviceCommand_Received;
		unsigned short receivedCmd = ((unsigned char)receivedData[15]);
		receivedCmd |=  			 ((unsigned char)receivedData[14])<<8;
		switch (receivedCmd)
		{
			case COMMAND_PLATEOUT:
				doorStatus = True;
				SerialThreadEvent->SetEvent();      // pra destravar a thread execute (sendCommand/execute)
				break;

			case COMMAND_PLATEIN:
				doorStatus = False;
				SerialThreadEvent->SetEvent();      // pra destravar a thread execute (sendCommand/execute)
				break;

			case COMMAND_CONNECT: {
				unsigned int idxDado = 20;//+12;

				unsigned int task_busy = 0;    // 0 ou 1
				task_busy = ((unsigned char)receivedData[idxDado++]);
				task_busy = ((unsigned char)receivedData[idxDado++]);
				task_busy = ((unsigned char)receivedData[idxDado++]);
				task_busy = ((unsigned char)receivedData[idxDado++]);

				unsigned int machine_busy = 0;    // 0 ou 1
				machine_busy = ((unsigned char)receivedData[idxDado++]);
				machine_busy = ((unsigned char)receivedData[idxDado++]);
				machine_busy = ((unsigned char)receivedData[idxDado++]);
				machine_busy = ((unsigned char)receivedData[idxDado++]);

				unsigned char pn[15];    // part number?
				for (int i = 0; i < 15; i++)
					pn[i] = ((unsigned char)receivedData[idxDado++]);

				unsigned int filtros_lidos[8];
				char qtd_filtros = 0;
				for (; qtd_filtros < 8; qtd_filtros++) {
					filtros_lidos[qtd_filtros] = 0;    // 0 ou 1
					filtros_lidos[qtd_filtros] = ((unsigned char)receivedData[idxDado++]);
					filtros_lidos[qtd_filtros] = ((unsigned char)receivedData[idxDado++]);
					filtros_lidos[qtd_filtros] = ((unsigned char)receivedData[idxDado++]);
					filtros_lidos[qtd_filtros] = ((unsigned char)receivedData[idxDado++]);

					if (filtros_lidos[qtd_filtros] == 0)
						break;
				}

				SerialThreadEvent->SetEvent();      // pra destravar a thread execute (sendCommand/execute)
			}
			break;

			case COMMAND_UNCONNECT:
				SerialThreadEvent->SetEvent();      // pra destravar a thread execute (sendCommand/execute)
				break;

			case COMMAND_MEASURE_PARAM:
				break;
			case COMMAND_RUN:
				break;

			case COMMAND_MEASURE:
			{
				unsigned int idxDado = 20;//+12;

				unsigned int plateCurrent = 0;
				plateCurrent = ((unsigned char)receivedData[idxDado++]);
				plateCurrent = ((unsigned char)receivedData[idxDado++]);
				plateCurrent = ((unsigned char)receivedData[idxDado++]);
				plateCurrent = ((unsigned char)receivedData[idxDado++]);

				unsigned int kinetic_readings_poractical = 0;
				kinetic_readings_poractical = ((unsigned char)receivedData[idxDado++]);
				kinetic_readings_poractical = ((unsigned char)receivedData[idxDado++]);
				kinetic_readings_poractical = ((unsigned char)receivedData[idxDado++]);
				kinetic_readings_poractical = ((unsigned char)receivedData[idxDado++]);

				unsigned int filterUsed = 0;
				filterUsed = ((unsigned char)receivedData[idxDado++]);
				filterUsed = ((unsigned char)receivedData[idxDado++]);
				filterUsed = ((unsigned char)receivedData[idxDado++]);
				filterUsed = ((unsigned char)receivedData[idxDado++]);

				for (RawDataMatrix::size_type row = 0; row < rawData.size(); row++)
				{
					for (ColumnsData::size_type col = 0; col < rawData[row].size(); col++)
					{
						union{
							unsigned char charValue[4];
							float floatValue;
						}PocosValue;

						PocosValue.floatValue = 0;
						PocosValue.charValue[3] = ((unsigned char)receivedData[idxDado++]);
						PocosValue.charValue[2] = ((unsigned char)receivedData[idxDado++]);
						PocosValue.charValue[1] = ((unsigned char)receivedData[idxDado++]);
						PocosValue.charValue[0] = ((unsigned char)receivedData[idxDado++]);

						rawData[row][col] = PocosValue.floatValue;
					}
				}

				// Se sao 2 filtrros a segunda leitura vem junto
				if (filterUsed >= 2 && qtdBytes > idxDado+2) {
					for (RawDataMatrix::size_type row = 0; row < rawDataFilter2.size(); row++)
					{
						for (ColumnsData::size_type col = 0; col < rawDataFilter2[row].size(); col++)
						{
							union{
								unsigned char charValue[4];
								float floatValue;
							}PocosValue;

							PocosValue.floatValue = 0;
							PocosValue.charValue[3] = ((unsigned char)receivedData[idxDado++]);
							PocosValue.charValue[2] = ((unsigned char)receivedData[idxDado++]);
							PocosValue.charValue[1] = ((unsigned char)receivedData[idxDado++]);
							PocosValue.charValue[0] = ((unsigned char)receivedData[idxDado++]);

							rawDataFilter2[row][col] = PocosValue.floatValue;

							// Ja modifica o valor com o valor calculado - checar se isso vai ser usado
							rawData[row][col] = calculaValueFilter2(rawData[row][col], PocosValue.floatValue);

						}
					}

				}


				if (IsReadEventStored())
					onReadEvent(this, rawData, rawDataFilter2);

				SerialThreadEvent->SetEvent();      // pra destravar a thread execute (sendCommand/execute)
				break;
			}

			case COMMAND_STOP:
				SerialThreadEvent->SetEvent();      // pra destravar a thread execute (sendCommand/execute)
				break;
			case COMMAND_CURR_BOARD:
				SerialThreadEvent->SetEvent();      // pra destravar a thread execute (sendCommand/execute)
				break;
			case COMMAND_ERRCODE:
				SerialThreadEvent->SetEvent();      // pra destravar a thread execute (sendCommand/execute)
				break;
			case COMMAND_NEXT_PLATE:
				SerialThreadEvent->SetEvent();      // pra destravar a thread execute (sendCommand/execute)
				break;
			case COMMAND_KINETIC:
				SerialThreadEvent->SetEvent();      // pra destravar a thread execute (sendCommand/execute)
				break;
			case COMMAND_VIEW:
				SerialThreadEvent->SetEvent();      // pra destravar a thread execute (sendCommand/execute)
				break;
			case COMMAND_SEND_PN:
				SerialThreadEvent->SetEvent();      // pra destravar a thread execute (sendCommand/execute)
				break;

		}

	} while (idxBufferFim > idxBufferIni);

	idxBufferFim = 0;
	idxBufferIni = 0;
}

////////////////////////////////////////////////////////////////////////////////
double __fastcall TLMR962023Device::calculaValueFilter2(double M1, double M2)
{
	double res = 0;
	switch (params->CalcMethod) {
	case 0: res = M1;
		break;
	case 1: res = M1 < M2 ? 0 : M1-M2;
		break;
	case 2: res = M2 == 0 ? -1 : M1/M2;
		break;
	case 3: res = M1+M2;
		break;
	case 4: res = M1*M2;
		break;
	case 5: res = M1 > M2 ? 0 : M2-M1;
		break;
	case 6: res = M1 == 0 ? -1 : M2/M1;
		break;
	}

	return res;
}

////////////////////////////////////////////////////////////////////////////////
Integer __fastcall TLMR962023Device::SendCommand(const ByteArray& cmd, bool waitResponse /*=false*/)
{
	lastErrorCode = 0;

	int sz = cmd.size();
	LMR962023SerialPortThread *thSerial = new LMR962023SerialPortThread(this, MyDataModule->ZylSerialPort, cmd, waitResponse);
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

void __fastcall TLMR962023Device::OnFault(TObject *Sender, TCommPort Port)
{
	using System::Sysutils::Format;

	MessageDlg(Format("Fatal error on port \"%s\"", ARRAYOFCONST((MyDataModule->ZylSerialPort->CommPortToString(Port)))),
			   mtError, TMsgDlgButtons() << mbOK, 0);

	SerialThreadMutex->Release();
	isFaulted = LastErrorCode;
}


StlStringList __fastcall TLMR962023Device::GetPortNames()
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

