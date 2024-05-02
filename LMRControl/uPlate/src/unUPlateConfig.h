//---------------------------------------------------------------------------

#ifndef unUPlateConfigH
#define unUPlateConfigH

#include <System.Classes.hpp>

#include "unElisaDevice.h"
#include "Singleton.h"

class uPlateConfig
{
	public:
		uPlateConfig();
		~uPlateConfig() {};

		__property ElisaDeviceTypeEnum DeviceType = {read = m_deviceType};

		void setDeviceType(ElisaDeviceTypeEnum type);

	private:
		ElisaDeviceTypeEnum m_deviceType;
};

typedef SingletonPattern<uPlateConfig> uPlateConfigSingleton;
//---------------------------------------------------------------------------
#endif
