//---------------------------------------------------------------------------

#ifndef unLMR96DeviceH
#define unLMR96DeviceH

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

class TLMR96Device;

class LMR96SerialPortThread : public TThread
{
	public:
		__fastcall LMR96SerialPortThread(TLMR96Device *_owner, TZylSerialPort *serial, const ByteArray& cmd);

		__property NativeInt ExitStatus = {read=GetExitStatus, write=SetExitStatus};

	protected:
		void __fastcall Execute();

		NativeInt __fastcall GetExitStatus();
		void __fastcall SetExitStatus(NativeInt status);

	private:
		TZylSerialPort *device;
		ByteArray cmdString;

		NativeInt exitStatus;
		TLMR96Device *owner;
};

class TLMR96Device : public TElisaDevice
{
		friend class LMR96SerialPortThread;

	public:
		__fastcall TLMR96Device(TComponent *owner = NULL);
		__fastcall ~TLMR96Device();

		Boolean __fastcall Connect(AnsiString commName);
		void __fastcall Disconnect();
		void __fastcall Terminate();

		void __fastcall sendDoorCommand(Boolean openClose);
		void __fastcall sendConnectCommand();
		void __fastcall sendDisconnectCommand();
		void __fastcall sendRunProgram();
		void __fastcall sendGetCapabilitiesCommand();
		void __fastcall sendGetFilterList();
		void __fastcall sendSetFilterList();
		void __fastcall sendGetStatus();
		Boolean __fastcall sendGetKey();
		void __fastcall sendSetParams() {}

		void __fastcall OnReceive(TObject* Sender, AnsiString Buffer);
		Integer __fastcall SendCommand(const ByteArray& cmd, bool waitResponse = false);

		StlStringList __fastcall GetPortNames();

	private:
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

typedef TLMR96Device * PLMR96Device;
//---------------------------------------------------------------------------
#endif
