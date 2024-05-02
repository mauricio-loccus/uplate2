//---------------------------------------------------------------------------
#include "unUPlateConfig.h"

#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)

uPlateConfig::uPlateConfig() : m_deviceType(ElisaDeviceTypeEnum::ElisaDeviceLMR96) {}

void uPlateConfig::setDeviceType(ElisaDeviceTypeEnum type)
{
	if (type == m_deviceType)
		return;

	m_deviceType = type;
}

