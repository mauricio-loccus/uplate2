//---------------------------------------------------------------------------

#ifndef unLMR962023DeviceH
#define unLMR962023DeviceH

#include "unElisaDevice.h"

#include <System.hpp>
#include <System.Classes.hpp>

#include <vector>
#include <string>
#include <memory>

#include "unElisaDevice.h"

#include <boost/array.hpp>

#include "unFrmWait.h"
#include "unDataModule.h"
#include "unStrUtils.h"
#include "memstream.h"

// Params USB
const Word ElisaVendorID = 0x1A86;
const Word ElisaProductID = 0x7523;

// Params protocol
// Comands send
#define COMMAND_CONNECT 		0x0001
#define COMMAND_UNCONNECT		0x0002
#define COMMAND_RUN				0x0003
#define COMMAND_STOP			0x0004
#define COMMAND_PLATEIN			0x0005
#define COMMAND_PLATEOUT		0x0006
#define COMMAND_NEXT_PLATE		0x0007
#define COMMAND_MEASURE_PARAM	0x0008
#define COMMAND_KINETIC			0x0009
#define COMMAND_VIEW			0x000A
#define COMMAND_SEND_PN			0x000B
// Commands recebidos
#define COMMAND_MEASURE			0x0100
#define COMMAND_CURR_BOARD		0x0200
#define COMMAND_ERRCODE			0x0300
//#define COMMAND_UNCONNECT		0x0500

/////////////////////
class TLMR962023Device;

class LMR962023SerialPortThread : public TThread
{
	public:
		__fastcall LMR962023SerialPortThread(TLMR962023Device *_owner, TZylSerialPort *serial, const ByteArray& cmd, bool _waitResponse);

		__property NativeInt ExitStatus = {read=GetExitStatus, write=SetExitStatus};

	protected:
		void __fastcall Execute();

		NativeInt __fastcall GetExitStatus();
		void __fastcall SetExitStatus(NativeInt status);

	private:
		TZylSerialPort *device;
		ByteArray cmdString;
	   	bool waitResponse;



		NativeInt exitStatus;
		TLMR962023Device *owner;
};

class TLMR962023Device : public TElisaDevice
{
		friend class LMR962023SerialPortThread;

	public:
		__fastcall TLMR962023Device(TComponent *owner = NULL);
		__fastcall ~TLMR962023Device();

		int findHeader(ByteArray arr, int posIni, int posFim);

		Boolean __fastcall Connect(AnsiString commName);
		void __fastcall Disconnect();
		void __fastcall Terminate();

		void __fastcall sendDoorCommand(Boolean openClose);
		void __fastcall sendConnectCommand();
		void __fastcall sendDisconnectCommand();
		void __fastcall sendSetParams();
		void __fastcall sendRunProgram();
		void __fastcall sendGetCapabilitiesCommand();
		void __fastcall sendGetFilterList();
		void __fastcall sendSetFilterList();
		void __fastcall sendGetStatus();
   		Boolean __fastcall sendGetKey() {};

		void __fastcall OnReceive(TObject* Sender, AnsiString Buffer);
		Integer __fastcall SendCommand(const ByteArray& cmd, bool waitResponse = false);

		StlStringList __fastcall GetPortNames();
        ByteArray checksum(ByteArray array);
		double __fastcall calculaValueFilter2(double M1, double M2);

	private:
		ByteArray bufferSerial;
		unsigned int idxBufferIni;
		unsigned int idxBufferFim;

		Boolean __fastcall GetConnectionStatus()
		{
			return MyDataModule->ZylSerialPort->IsConnected();
		}

		/**//*******************************************************************
		 * Global synchronization objects
		 ***********************************************************************/
		TEvent *SerialThreadEvent;
		TMutex *SerialThreadMutex;

		void __fastcall OnFault(TObject* Sender, TCommPort Port);
};

typedef TLMR962023Device * PLMR962023Device;
//---------------------------------------------------------------------------
#endif
