//---------------------------------------------------------------------------
#include <vcl.h>

#pragma hdrstop

#include "unElisaSimulator.h"

#include "unFrmSimulatedValues.h"
#include <iostream>

//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TElisaSimulator::TElisaSimulator(TComponent *owner) : TElisaDevice(owner)
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
}
__fastcall TElisaSimulator::~TElisaSimulator()
{
	if (FrmSimulatedValues)
	{
		FrmSimulatedValues->Free();
		FrmSimulatedValues = NULL;
	}
}

Boolean __fastcall TElisaSimulator::Connect(AnsiString commName)
{
	authenticated = True;
	return authenticated;
}

StlStringList __fastcall TElisaSimulator::GetPortNames()
{
	return StlStringList(1, TEXT("NullPort"));
}

void __fastcall TElisaSimulator::sendDoorCommand(Boolean openClose)
{
	SendCommand();
}

void __fastcall TElisaSimulator::sendConnectCommand() {}
void __fastcall TElisaSimulator::sendDisconnectCommand() {}

void __fastcall TElisaSimulator::sendRunProgram()
{
	currCommand = ElisaCommands::ElisaCommand_RunProgram;

	SendCommand();
}

void __fastcall TElisaSimulator::sendGetCapabilitiesCommand() {}
void __fastcall TElisaSimulator::sendGetFilterList() {}
void __fastcall TElisaSimulator::sendSetFilterList() {}
void __fastcall TElisaSimulator::sendGetStatus() {}

void __fastcall TElisaSimulator::OnReceive(TObject* Sender, AnsiString)
{
	switch (currCommand)
	{
		case ElisaCommands::ElisaCommand_OpenDoor:
			currCommand = ElisaCommands::ElisaCommand_OpenDoor;
			break;

		case ElisaCommands::ElisaCommand_CloseDoor:
			currCommand = ElisaCommands::ElisaCommand_CloseDoor;
			break;

		case ElisaCommands::ElisaCommand_GetDefaultValue:
		case ElisaCommands::ElisaCommand_OpenConnection:
		case ElisaCommands::ElisaCommand_CloseConnection:
		case ElisaCommands::ElisaCommand_GetFiltersList:
		case ElisaCommands::ElisaCommand_GetStatus:
		case ElisaCommands::ElisaCommand_SetFiltersList:
		case ElisaCommands::ElisaCommand_StopExecution:
		case ElisaCommands::ElisaCommand_GetKey:
			break;

		case ElisaCommands::ElisaCommand_RunProgram:
		{
			FrmSimulatedValues = new TFrmSimulatedValues(rawData);
			FrmSimulatedValues->ShowModal();
			FrmSimulatedValues->Free();

			if (IsReadEventStored())
				onReadEvent(this, rawData, rawData);

			break;
		}

		default:
			std::cout << "CODE >>>> " << int(currCommand) << std::endl;
			throw Exception(TEXT("Comando não reconhecido"));
	}
}

Integer __fastcall TElisaSimulator::SendCommand(const ByteArray& cmd, bool waitResponse)
{
	OnReceive(this);
	return 0;
}

