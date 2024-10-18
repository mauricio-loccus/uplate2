//---------------------------------------------------------------------------

#ifndef unElisaSimulatorH
#define unElisaSimulatorH

#include "unElisaDevice.h"

class TElisaSimulator : public TElisaDevice
{
	public:
		__fastcall TElisaSimulator(TComponent *owner = NULL);
		__fastcall ~TElisaSimulator();

		Boolean __fastcall Connect(AnsiString commName);
		void __fastcall Disconnect() {}
		void __fastcall Terminate() {}

		void __fastcall sendDoorCommand(Boolean openClose);
		void __fastcall sendConnectCommand();
		void __fastcall sendDisconnectCommand();
		void __fastcall sendRunProgram();
		void __fastcall sendGetCapabilitiesCommand();
		void __fastcall sendGetFilterList();
		void __fastcall sendSetFilterList();
		void __fastcall sendGetStatus();
		Boolean __fastcall sendGetKey() { return True; }
		void __fastcall sendSetParams() {}

		StlStringList __fastcall GetPortNames();

		void __fastcall OnReceive(TObject* Sender, AnsiString = AnsiString());
		Integer __fastcall SendCommand(const ByteArray& cmd = ByteArray(), bool waitResponse = false);

		Boolean __fastcall GetConnectionStatus()
		{
            return True;
		}
};
//---------------------------------------------------------------------------
#endif
