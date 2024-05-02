//---------------------------------------------------------------------------

#ifndef unDeviceFactoryH
#define unDeviceFactoryH

#include "Singleton.h"
#include "unElisaDevice.h"

class DeviceFactory
{
	public:
		__fastcall DeviceFactory() {}
		__fastcall ~DeviceFactory() {}

		PElisaDevice __fastcall CreateDevice(ElisaDeviceTypeEnum type);

	private:
		__fastcall DeviceFactory(const DeviceFactory&);
};
typedef SingletonPattern<DeviceFactory> DeviceFactorySingleton;
//---------------------------------------------------------------------------
#endif
