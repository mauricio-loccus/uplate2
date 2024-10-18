//---------------------------------------------------------------------------

#ifndef unElisaDeviceH
#define unElisaDeviceH

#include <System.hpp>
#include <System.Classes.hpp>

#include <vector>
#include <string>
#include <memory>

#include <boost/array.hpp>

#include "Elisa.h"
#include "unParams.h"
#include "Singleton.h"
#include "unStrUtils.h"

typedef boost::array<Double, 12> ColumnsData;
typedef boost::array<ColumnsData, 8> RawDataMatrix;

enum class ElisaCommands : Word
{
	ElisaCommand_OpenDoor           = 0x08,
	ElisaCommand_CloseDoor          = 0x09,
	ElisaCommand_GetDefaultValue    = 0x14,
	ElisaCommand_OpenConnection     = 0x15,
	ElisaCommand_CloseConnection    = 0x16,
	ElisaCommand_GetFiltersList		= 0x17,
	ElisaCommand_GetKey			    = 0x18,
	ElisaCommand_RunProgram  		= 0x19,
	ElisaCommand_GetStatus 			= 0x20,

	ElisaCommand_SetFiltersList		= 0x21,

	ElisaCommand_StopExecution      = 0x1E
};

enum class ElisaDeviceTypeEnum : Word
{
	ElisaDeviceLMR96_2023, // new one - qt
	ElisaDeviceLMR96,
	ElisaDeviceLMR96Flex,
	ElisaDeviceLRM96Simulator
};

enum class ElisaDeviceCommandStatus : Word
{
	ElisaDeviceCommand_Sended = 0x00,
	ElisaDeviceCommand_Received,
	ElisaDeviceCommand_Idle
};

enum class ElisaDeviceRunModeStatus : Word
{
	ElisaDeviceRunMode_IDLE = 0,
	ElisaDeviceRunMode_PLATE_IN,
	ElisaDeviceRunMode_PLATE_OUT,
	ElisaDeviceRunMode_STOP,
	ElisaDeviceRunMode_MEASURE,
	ElisaDeviceRunMode_SHAKE,
	ElisaDeviceRunMode_SELFTEST,
	ElisaDeviceRunMode_FILTER,
	ElisaDeviceRunMode_CALIBRATE_ORIGIN,
	ElisaDeviceRunMode_SAVE_ORIGIN,
	ElisaDeviceRunMode_INTENSITY_TEST,
	ElisaDeviceRunMode_MAX
};

typedef void __fastcall (__closure *TElisaReadNotifyEvent)(System::TObject *Sender, const RawDataMatrix& rawMatrix, const RawDataMatrix& rawMatrixFilter2);
typedef void __fastcall (__closure *TElisaAboutToStartNotifyEvent)(System::TObject *Sender);
typedef void __fastcall (__closure *TElisaAboutToFinishNotifyEvent)(System::TObject *Sender);
typedef void __fastcall (__closure *TElisaCommunicationTimeoutNotifyEvent)(System::TObject *Sender);

class TElisaDevice : public TObject
{
	public:
		__fastcall TElisaDevice(TComponent *owner = NULL);
		virtual __fastcall ~TElisaDevice() {};

		virtual Boolean __fastcall Connect(AnsiString commName) = 0;
		virtual void __fastcall Disconnect() = 0;
		virtual void __fastcall Terminate() = 0;

		virtual void __fastcall sendDoorCommand(Boolean openClose) = 0;
		virtual void __fastcall sendConnectCommand() = 0;
		virtual void __fastcall sendDisconnectCommand() = 0;
		virtual void __fastcall sendRunProgram() = 0;
		virtual void __fastcall sendGetCapabilitiesCommand() = 0;
		virtual void __fastcall sendGetFilterList() = 0;
		virtual void __fastcall sendSetFilterList() = 0;
		virtual void __fastcall sendGetStatus() = 0;
		virtual Boolean __fastcall sendGetKey() = 0;
        virtual void __fastcall sendSetParams() = 0;
		virtual StlStringList __fastcall GetPortNames() = 0;

	public:
		__property Boolean isConnected = {read = GetConnectionStatus};
		__property Boolean DoorStatus = {read = doorStatus};
		__property const RawDataMatrix RawData = {read = rawData};
		__property Boolean isAuthenticated = {read = authenticated};
		__property ElisaDeviceRunModeStatus RunMode = {read = runStatus};
		__property Integer LastErrorCode = {read = lastErrorCode};
		__property ElisaDeviceTypeEnum Type = {read = mDeviceType};
		__property ElisaDeviceCommandStatus Status = {read = commandStatus, default = ElisaDeviceCommandStatus::ElisaDeviceCommand_Idle};

		__property TElisaReadNotifyEvent OnRead = {read=onReadEvent, write=onReadEvent, stored=IsReadEventStored};
		__property TElisaAboutToStartNotifyEvent OnAboutStart = {read=onAboutToStartEvent, write=onAboutToStartEvent, stored=IsAboutToStartEventStored};
		__property TElisaAboutToFinishNotifyEvent OnAboutToFinish = {read=onAboutToFinishEvent, write=onAboutToFinishEvent, stored=IsAboutToFinishEventStored};

		__property const BOARD_INF& DefaultValue = {read = GetDefaultValue};
		__property FILTERLUN Filters = {read = m_Filters, write = m_Filters};
		__property ElisaParams * Params = {read = params, write = params};

		__property const RawDataMatrix RawDataFilter2 = {read = rawDataFilter2};

	protected:
		const BOARD_INF& __fastcall GetDefaultValue()
		{
			return board_inf;
		}

		Boolean IsAboutToStartEventStored()
		{
			return onAboutToStartEvent != NULL;
		}

		Boolean __fastcall IsAboutToFinishEventStored()
		{
			return onAboutToFinishEvent != NULL;
		}

		Boolean __fastcall IsReadEventStored()
		{
			return onReadEvent != NULL;
		}

		virtual Boolean __fastcall GetConnectionStatus() = 0;

	protected:
		FILTERLUN m_Filters;
		BOARD_INF board_inf;

		TComponent *mParent;

		Boolean doorStatus;
		Boolean authenticated;
		Boolean isFaulted;

		ElisaCommands currCommand;
		ElisaDeviceCommandStatus commandStatus;

		RawDataMatrix rawData;
		RawDataMatrix rawDataFilter2;

		ElisaDeviceRunModeStatus runStatus;
		Integer lastErrorCode;

		ElisaDeviceTypeEnum mDeviceType;

		TElisaReadNotifyEvent onReadEvent;
		TElisaAboutToStartNotifyEvent onAboutToStartEvent;
		TElisaAboutToFinishNotifyEvent onAboutToFinishEvent;
		TElisaCommunicationTimeoutNotifyEvent onCommunicationTimeoutEvent;
		ElisaParams *params;

		/**//*******************************************************************
		 * Global synchronization objects
		 ***********************************************************************/
		virtual void __fastcall OnReceive(TObject* Sender, AnsiString Buffer) = 0;
		virtual Integer __fastcall SendCommand(const ByteArray& cmd, bool waitResponse = false) = 0;
};
//---------------------------------------------------------------------------

typedef TElisaDevice* PElisaDevice;

extern const Word ElisaVendorID;
extern const Word ElisaProductID;
extern const LPCSTR ElisaHashKey;
extern const Word ElisaHashKeyLength;

const StlString GetHardwareID(const StlString& commName);
Word deviceVendorIdentifier(const StlString& instanceIdentifier, bool &ok);
Word deviceProductIdentifier(const StlString& instanceIdentifier, bool &ok);

StlString parseDeviceSerialNumber(const StlString& instanceIdentifier);

#endif
