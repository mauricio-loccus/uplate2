//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#pragma hdrstop

#include "unDeviceFactory.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "unElisaSimulator.h"
#include "unLMR962023Device.h"
#include "unLMR96Device.h"
#include "unUPlateConfig.h"
#include <iostream>

PElisaDevice __fastcall DeviceFactory::CreateDevice(ElisaDeviceTypeEnum type)
{
	PElisaDevice pDevice(NULL);

	switch (type)
	{
		case ElisaDeviceTypeEnum::ElisaDeviceLMR96_2023:
			pDevice = new TLMR962023Device();
			break;

		case ElisaDeviceTypeEnum::ElisaDeviceLMR96:
			pDevice = new TLMR96Device();
			break;

		case ElisaDeviceTypeEnum::ElisaDeviceLMR96Flex:
			break;

		case ElisaDeviceTypeEnum::ElisaDeviceLRM96Simulator:
			pDevice = new TElisaSimulator();
			break;

		default:
			throw Exception("Dispositivo não suportado.");
	}

	uPlateConfigSingleton::instance()->setDeviceType(type);

	return pDevice;
}
