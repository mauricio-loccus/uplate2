//---------------------------------------------------------------------------

#pragma hdrstop

#include "unWell.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

String __fastcall TWell::typeToString()
{
	switch (mType)
    {
		case TWellType::wlEmpty:
			return TEXT("Vazio");

		case TWellType::wlBlank:
			return TEXT("Branco");

		case TWellType::wlNegativeControl:
			return TEXT("Controle Negativo");

		case TWellType::wlPositiveControl:
			return TEXT("Controle Positivo");

		case TWellType::wlUnknown:
			return TEXT("Desconhecido");

		case TWellType::wlConcentrationStd:
			return TEXT("Standard");

		case TWellType::wlQualityControl:
			return TEXT("Controle de Qualidade");
	}

	return String();
}