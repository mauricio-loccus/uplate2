//---------------------------------------------------------------------------
#include <Vcl.h>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <SDL_math2.hpp>
#include <limits>

#pragma hdrstop

#include "unWellMatrix.h"
#include "unDataModule.h"

#include "unFrmMain.h"
#include "unLoccusLinFit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LMDVistaDialogs"
#pragma resource "*.dfm"

static const String DirSeparators("\\/");
const Double StepResolution = 50.0;

TMyDataModule *MyDataModule;
//---------------------------------------------------------------------------
__fastcall TMyDataModule::TMyDataModule(TComponent* Owner)
	: TDataModule(Owner)
{
curveFit = new TCurveFit(this);
}
//---------------------------------------------------------------------------

Boolean __fastcall TMyDataModule::CalcLinearCurveFit(CalibrationData& refCalibrationCurve)
{
	using System::Sysutils::Format;

	WellMatrixList& wellMatrixListRef = (*TWellMatrixSingleton::instance());
	DoubleArray arrStd, arrAbs, arrConc;
	Double r2 = 0;

	WellList conclp;
	wellMatrixListRef.front().filterWellsByType(TWellType::wlConcentrationStd, conclp);

    curveFit->Init();

    if (!MainForm->mCurveImported)
    {
        if (conclp.empty())
            return True;

		std::sort(conclp.begin(), conclp.end());

		WellList::iterator last = std::unique(conclp.begin(), conclp.end());

		WellList::size_type unElements = std::distance(conclp.begin(), last);
		conclp.resize(unElements);

		for (WellList::const_iterator it = conclp.begin(); it != conclp.end(); ++it)
		{
			WellListPointers wlp = wellMatrixListRef.front().getAllReplicas(*it);

			Double accRawBlankReduced = 0;

			for (WellListPointers::const_iterator cit = wlp.begin(); cit != wlp.end(); cit++)
				accRawBlankReduced += (*cit)->RawBlankReducedValue;

			Double avgRawBlankReduced = accRawBlankReduced / std::max<Double>(wlp.size(), 0.000001);

			for (WellListPointers::iterator wit = wlp.begin(); wit != wlp.end(); wit++)
				(*wit)->RawBlankReducedValue = avgRawBlankReduced;
		}

		for (WellList::const_iterator it = conclp.begin(); it != conclp.end(); ++it)
		{
			arrAbs.push_back(it->RawBlankReducedValue);
			arrStd.push_back(it->StdValue);
		}
	}
	else
	{
		std::vector< std::pair<Double, Double> >::const_iterator it;
		for (it = refCalibrationCurve.stdValues.begin(); it != refCalibrationCurve.stdValues.end(); it++)
		{
			arrAbs.push_back(it->first);
			arrStd.push_back(it->second);
		}
	}

    for (DoubleArray::size_type i = 0; i < arrStd.size(); i++)
    {
        Double x = arrAbs[i];
        Double y = arrStd[i];

        curveFit->EnterStatValue(x, y);
    }

	Double a = 0;
	Double b = 0;
	Double FitQual = 0;

	Boolean nearSingular = False;
	std::unique_ptr<Double> kArray(new Double[2]);

	// Obtemos a equação da curva
	try
	{
		curveFit->CalcPolyFit(1, kArray.get(), 2, FitQual, nearSingular);
	}
	catch (const Exception& e)
	{
		MessageDlg(e.Message, mtError, TMsgDlgButtons() << mbOK, 0);

		return False;
	}

	a = kArray.get()[1];
	b = kArray.get()[0];

	// Aplica o cálculo da concentração a todas a células diferentes de Vazio.
	for (WellMatrixList::size_type i = 0; i < wellMatrixListRef.size(); i++)
	{
		TWellMatrix& refMatrix = wellMatrixListRef[i];

		for (Integer row = 0; row < MainForm->m_elisaDeviceParams->PlateRows; row++)
		{
			for (WellList::iterator it = refMatrix[row].begin(); it != refMatrix[row].end(); it++)
			{
				if (it->Type == TWellType::wlEmpty)
					continue;

				Double v = it->RawBlankReducedValue * a + b;
				it->ConcentrationValue = std::max(0.0, v);
			}
		}
	}

	for (WellList::const_iterator it = conclp.begin(); it != conclp.end(); ++it)
	{
		WellListPointers wlp = wellMatrixListRef.front().getAllReplicas(*it);

		Double accConc = 0;

		for (WellListPointers::const_iterator cit = wlp.begin(); cit != wlp.end(); cit++)
			accConc += (*cit)->ConcentrationValue;

		Double avgConc = accConc / std::max<Double>(wlp.size(), 0.000001);

		for (WellListPointers::iterator wit = wlp.begin(); wit != wlp.end(); wit++)
			(*wit)->ConcentrationValue = avgConc;
	}

	curveFit->Init();

	for (DoubleArray::size_type i = 0; i < arrStd.size(); i++)
	{
		Double x = arrStd[i];
		Double y = arrAbs[i];

		curveFit->EnterStatValue(x, y);
	}

	a = 0;
	b = 0;
	FitQual = 0;

	kArray.reset(new Double[2]);

	// Obtemos a equação da curva
	try
	{
		curveFit->CalcPolyFit(1, kArray.get(), 2, FitQual, nearSingular);
	}
	catch (const Exception& e)
	{
		MessageDlg(e.Message, mtError, TMsgDlgButtons() << mbOK, 0);

		return False;
	}

	a = kArray.get()[1];
	b = kArray.get()[0];

	// Varre a placa para isolar o valor máximo.
	Double maxValPlate = 0;

	for (WellMatrixList::size_type i = 0; i < wellMatrixListRef.size(); i++)
	{
		TWellMatrix& refMatrix = wellMatrixListRef[i];

		for (Integer row = 0; row < MainForm->m_elisaDeviceParams->PlateRows; row++)
		{
			for (WellList::iterator it = refMatrix[row].begin(); it != refMatrix[row].end(); it++)
			{
				if (it->Type == TWellType::wlEmpty)
					continue;

				maxValPlate = std::max(maxValPlate, std::max(it->StdValue, it->ConcentrationValue));
			}
		}
	}

	// Determinar o "step" do gráfico.
	Double step = maxValPlate / StepResolution;

	Double maxValue = std::max<Double>(*std::max_element(arrAbs.begin(), arrAbs.end()), 0);
	Double minValue = *std::min_element(arrAbs.begin(), arrAbs.end());

	MainForm->stdCurveChart->LeftAxis->Maximum = maxValue;
	MainForm->stdCurveChart->LeftAxis->Minimum = std::min(minValue, maxValue);

	MainForm->stdCurveChart->BottomAxis->Minimum = 0;
	MainForm->stdCurveChart->BottomAxis->Maximum = std::max<Double>(maxValPlate, 0);
	MainForm->stdCurveChart->BottomAxis->Increment = (Double)((Integer)maxValPlate / 10.0);

	// Determina-se o array de plot da curva;
	MainForm->curveSerie->Clear();
	MainForm->curveSerie->BeginUpdate();

	for (Double x = minValue; x <= maxValPlate; x += step)
	{
		Double y = x * a + b;

		MainForm->curveSerie->AddXY(x, y);
	}

	MainForm->curveSerie->EndUpdate();

	// Plotar os pontos dos padrões
	MainForm->pointsSerie->Clear();
	MainForm->pointsSerie->BeginUpdate();
	for (DoubleArray::size_type i = 0; i < arrStd.size(); i++)
	{
		Double x = arrStd[i];
		Double y = arrAbs[i];

		MainForm->pointsSerie->AddXY(x, y);

        if (!MainForm->mCurveImported)
            refCalibrationCurve.stdValues.push_back(std::pair<Double, Double>(x, y));
	}
	MainForm->pointsSerie->EndUpdate();

	String r2Text = Format(_T("R2 = %5.3f"), ARRAYOFCONST((FitQual)));

	MainForm->lbR2->Caption = r2Text;

	MainForm->stdCurveChart->SubTitle->Text->SetText(Format(TEXT("y = %5.3f * x + %5.3f"), ARRAYOFCONST((a, b))).c_str());

    refCalibrationCurve.qtdParameters = 2;
    refCalibrationCurve.parameters.push_back(a);
	refCalibrationCurve.parameters.push_back(b);

    if (!MainForm->mCurveImported)
        refCalibrationCurve.timestamp = Now();

	return True;
}

Boolean __fastcall TMyDataModule::CalcLinearCurveFitCrossOrigin(CalibrationData& refCalibrationCurve)
{
	using System::Sysutils::Format;

	WellMatrixList& wellMatrixListRef = (*TWellMatrixSingleton::instance());

	DoubleArray arrStd, arrAbs, arrConc;
	Double r2 = 0;

	WellList conclp;
	wellMatrixListRef.front().filterWellsByType(TWellType::wlConcentrationStd, conclp);

    if (!MainForm->mCurveImported)
    {
        if (conclp.empty())
            return True;

		std::sort(conclp.begin(), conclp.end());

		WellList::iterator last = std::unique(conclp.begin(), conclp.end());

		WellList::size_type unElements = std::distance(conclp.begin(), last);
		conclp.resize(unElements);

		for (WellList::const_iterator it = conclp.begin(); it != conclp.end(); ++it)
		{
			WellListPointers wlp = wellMatrixListRef.front().getAllReplicas(*it);

			Double accRawBlankReduced = 0;

			for (WellListPointers::const_iterator cit = wlp.begin(); cit != wlp.end(); cit++)
				accRawBlankReduced += (*cit)->RawBlankReducedValue;

			Double avgRawBlankReduced = accRawBlankReduced / std::max<Double>(wlp.size(), 0.000001);

			for (WellListPointers::iterator wit = wlp.begin(); wit != wlp.end(); wit++)
				(*wit)->RawBlankReducedValue = avgRawBlankReduced;
		}

		for (WellList::const_iterator it = conclp.begin(); it != conclp.end(); ++it)
		{
			arrAbs.push_back(it->RawBlankReducedValue);
			arrStd.push_back(it->StdValue);
		}
	}
	else
	{
		std::vector< std::pair<Double, Double> >::const_iterator it;
		for (it = refCalibrationCurve.stdValues.begin(); it != refCalibrationCurve.stdValues.end(); it++)
		{
			arrAbs.push_back(it->first);
			arrStd.push_back(it->second);
		}
	}

    for (DoubleArray::size_type i = 0; i < arrStd.size(); i++)
    {
        Double x = arrAbs[i];
        Double y = arrStd[i];

        curveFit->EnterStatValue(x, y);
    }

	Double a = 0;
	Double b = 0;
	Double FitQual = 0;

	// Obtemos a equação da curva
	try
	{
		if (!LinFitCrossOrigin(arrAbs, arrStd, a, b, FitQual))
			throw Exception("Erro no algoritmo de LinFitCrossOrigin");
	}
	catch (const Exception& e)
	{
		MessageDlg(e.Message, mtError, TMsgDlgButtons() << mbOK, 0);

		return False;
	}

	// Aplica o cálculo da concentração a todas a células diferentes de Vazio.
	for (WellMatrixList::size_type i = 0; i < wellMatrixListRef.size(); i++)
	{
		TWellMatrix& refMatrix = wellMatrixListRef[i];

		for (Integer row = 0; row < MainForm->m_elisaDeviceParams->PlateRows; row++)
		{
			for (WellList::iterator it = refMatrix[row].begin(); it != refMatrix[row].end(); it++)
			{
				if (it->Type == TWellType::wlEmpty)
					continue;

				Double v = it->RawBlankReducedValue * a;
				it->ConcentrationValue = std::max<Double>(0.0, v);
			}
		}
	}

	for (WellList::const_iterator it = conclp.begin(); it != conclp.end(); ++it)
	{
		WellListPointers wlp = wellMatrixListRef.front().getAllReplicas(*it);

		Double accConc = 0;

		for (WellListPointers::const_iterator cit = wlp.begin(); cit != wlp.end(); cit++)
			accConc += (*cit)->ConcentrationValue;

		Double avgConc = accConc / std::max<Double>(wlp.size(), 0.000001);

		for (WellListPointers::iterator wit = wlp.begin(); wit != wlp.end(); wit++)
			(*wit)->ConcentrationValue = avgConc;
	}

	a = 0;
	b = 0;
	FitQual = 0;

	// Obtemos a equação da curva
	try
	{
		if (!LinFitCrossOrigin(arrStd, arrAbs, a, b, FitQual))
			throw Exception("Erro no algoritmo de LinFitCrossOrigin");
	}
	catch (const Exception& e)
	{
		MessageDlg(e.Message, mtError, TMsgDlgButtons() << mbOK, 0);

		return False;
	}

	// Varre a placa para isolar o valor máximo.
	Double maxValPlate = 0;

	for (WellMatrixList::size_type i = 0; i < wellMatrixListRef.size(); i++)
	{
		TWellMatrix& refMatrix = wellMatrixListRef[i];

		for (Integer row = 0; row < MainForm->m_elisaDeviceParams->PlateRows; row++)
		{
			for (WellList::iterator it = refMatrix[row].begin(); it != refMatrix[row].end(); it++)
			{
				if (it->Type == TWellType::wlEmpty)
					continue;

				maxValPlate = std::max(maxValPlate, std::max(it->StdValue, it->ConcentrationValue));
			}
		}
	}

	// Determinar o "step" do gráfico.
	Double step = maxValPlate / StepResolution;
	Double maxValue = std::max<Double>(*std::max_element(arrAbs.begin(), arrAbs.end()), 0);
	Double minValue = *std::min_element(arrAbs.begin(), arrAbs.end());

	MainForm->stdCurveChart->LeftAxis->Maximum = maxValue;
	MainForm->stdCurveChart->LeftAxis->Minimum = std::min(minValue, maxValue);

	MainForm->stdCurveChart->BottomAxis->Minimum = 0;
	MainForm->stdCurveChart->BottomAxis->Maximum = std::max<Double>(maxValPlate, 0);
	MainForm->stdCurveChart->BottomAxis->Increment = (Double)((Integer)maxValPlate / 10.0);

	MainForm->curveSerie->Clear();
	MainForm->curveSerie->BeginUpdate();
	// Determina-se o array de plot da curva;
	for (Double x = 0; x <= maxValPlate; x += step)
	{
		Double y = x * a;

		MainForm->curveSerie->AddXY(x, y);
	}
	MainForm->curveSerie->EndUpdate();

	// Plotar os pontos dos padrões

    MainForm->pointsSerie->Clear();
	MainForm->pointsSerie->BeginUpdate();
	for (DoubleArray::size_type i = 0; i < arrStd.size(); i++)
	{
		Double x = arrStd[i];
		Double y = arrAbs[i];

		MainForm->pointsSerie->AddXY(x, y);

		if (!MainForm->mCurveImported)
            refCalibrationCurve.stdValues.push_back(std::pair<Double, Double>(x, y));
	}
	MainForm->pointsSerie->EndUpdate();

	String r2Text = Format(TEXT("R2 = %5.3f"), ARRAYOFCONST((FitQual)));

	MainForm->lbR2->Caption = r2Text;

	MainForm->stdCurveChart->SubTitle->Text->SetText(Format(TEXT("y = %5.3f * x"), ARRAYOFCONST((a, b))).c_str());

	refCalibrationCurve.qtdParameters = 2;
    refCalibrationCurve.parameters.push_back(a);
    refCalibrationCurve.parameters.push_back(b);

    refCalibrationCurve.timestamp = Now();

	if (!MainForm->mCurveImported)
        refCalibrationCurve.timestamp = Now();

	return True;
}

Boolean __fastcall TMyDataModule::CalcLinearLogCurveFit(CalibrationData& refCalibrationCurve)
{
	using System::Sysutils::Format;

	WellMatrixList& wellMatrixListRef = (*TWellMatrixSingleton::instance());

	DoubleArray arrStd, arrAbs, arrConc;
	Double r2 = 0;

	WellList conclp;
    wellMatrixListRef.front().filterWellsByType(TWellType::wlConcentrationStd, conclp);

    curveFit->Init();

    if (!MainForm->mCurveImported)
    {
        if (conclp.empty())
            return True;

		std::sort(conclp.begin(), conclp.end());

		WellList::iterator last = std::unique(conclp.begin(), conclp.end());

		WellList::size_type unElements = std::distance(conclp.begin(), last);
		conclp.resize(unElements);

		Double accRawBlankReduced = 0;

		for (WellList::const_iterator it = conclp.begin(); it != conclp.end(); ++it)
		{
			WellListPointers wlp = wellMatrixListRef.front().getAllReplicas(*it);

			for (WellListPointers::const_iterator cit = wlp.begin(); cit != wlp.end(); cit++)
				accRawBlankReduced += (*cit)->RawBlankReducedValue;

			Double avgRawBlankReduced = accRawBlankReduced / std::max<Double>(wlp.size(), 0.000001);

			for (WellListPointers::iterator wit = wlp.begin(); wit != wlp.end(); wit++)
				(*wit)->RawBlankReducedValue = avgRawBlankReduced;
		}

		for (WellList::const_iterator it = conclp.begin(); it != conclp.end(); ++it)
		{
			arrAbs.push_back(it->RawBlankReducedValue);
			arrStd.push_back(it->StdValue);
		}
	}
	else
	{
		std::vector< std::pair<Double, Double> >::const_iterator it;
		for (it = refCalibrationCurve.stdValues.begin(); it != refCalibrationCurve.stdValues.end(); it++)
		{
			arrAbs.push_back(it->first);
			arrStd.push_back(it->second);
		}
	}

    for (DoubleArray::size_type i = 0; i < arrStd.size(); i++)
    {
        Double x = arrAbs[i];
        Double y = arrStd[i];

        curveFit->EnterStatValue(x, y);
    }

	Double a = 0;
	Double b = 0;
	Double FitQual = 0;

	// Obtemos a equação da curva
	try
	{
		curveFit->CalcLogFit(b, a, FitQual);
	}
	catch (const Exception& e)
	{
		TaskMessageDlg(TEXT("Atenção"),
					   TEXT("Para uma calibração com curva Logarítmica, os valores devem ser positivos."),
					   mtError,
					   TMsgDlgButtons() << mbOK, 0);

		return False;
	}

	// Aplica o cálculo da concentração a todas a células diferentes de Vazio.
	for (WellMatrixList::size_type i = 0; i < wellMatrixListRef.size(); i++)
	{
        TWellMatrix& refMatrix = wellMatrixListRef[i];

		for (Integer row = 0; row < MainForm->m_elisaDeviceParams->PlateRows; row++)
		{
			WellList& wlRef = refMatrix[row];

			for (WellList::iterator it = wlRef.begin(); it != wlRef.end(); it++)
			{
				if (it->Type == TWellType::wlEmpty)
					continue;

				Double v = a * std::log(std::max(it->RawBlankReducedValue, 0.0001)) + b;
				it->ConcentrationValue = std::max(0.0, v);
			}
		}
	}

	for (WellList::const_iterator it = conclp.begin(); it != conclp.end(); ++it)
	{
		WellListPointers wlp = wellMatrixListRef.front().getAllReplicas(*it);

		Double accConc = 0;

		for (WellListPointers::const_iterator cit = wlp.begin(); cit != wlp.end(); cit++)
			accConc += (*cit)->ConcentrationValue;

		Double avgConc = accConc / std::max<Double>(wlp.size(), 0.000001);

		for (WellListPointers::iterator wit = wlp.begin(); wit != wlp.end(); wit++)
			(*wit)->ConcentrationValue = avgConc;
	}

	curveFit->Init();

	for (DoubleArray::size_type i = 0; i < arrStd.size(); i++)
	{
		Double x = arrStd[i];
		Double y = arrAbs[i];

		curveFit->EnterStatValue(x, y);
	}

	a = 0;
	b = 0;
	FitQual = 0;

	// Obtemos a equação da curva
	try
	{
		curveFit->CalcLogFit(b, a, FitQual);
	}
	catch (const Exception& e)
	{
		TaskMessageDlg(TEXT("Atenção"),
					   TEXT("Para uma calibração com curva Logarítmica, os valores devem ser positivos."),
					   mtError,
					   TMsgDlgButtons() << mbOK, 0);

		return False;
	}

	// Varre a placa para isolar o valor máximo.
	Double maxValPlate = 0;

	for (WellMatrixList::size_type i = 0; i < wellMatrixListRef.size(); i++)
	{
		TWellMatrix& refMatrix = wellMatrixListRef[i];

		for (Integer row = 0; row < MainForm->m_elisaDeviceParams->PlateRows; row++)
		{
			for (WellList::iterator it = refMatrix[row].begin(); it != refMatrix[row].end(); it++)
			{
				if (it->Type == TWellType::wlEmpty)
					continue;

				maxValPlate = std::max(maxValPlate, std::max(it->StdValue, it->ConcentrationValue));
			}
		}
	}

	// Determinar o "step" do gráfico.
	Double step = maxValPlate / StepResolution;
	Double maxValue = std::max<Double>(*std::max_element(arrAbs.begin(), arrAbs.end()), 0);
	Double minValue = *std::min_element(arrAbs.begin(), arrAbs.end());

	MainForm->stdCurveChart->LeftAxis->Maximum = maxValue;
	MainForm->stdCurveChart->LeftAxis->Minimum = std::min(minValue, maxValue);

	MainForm->stdCurveChart->BottomAxis->Minimum = 0;
	MainForm->stdCurveChart->BottomAxis->Maximum = std::max<Double>(maxValPlate, 0);
	MainForm->stdCurveChart->BottomAxis->Increment = (Double)((Integer)maxValPlate / 10.0);

	// Determina-se o array de plot da curva;
	const Double initVal = std::pow(2.718, -b/a);

	MainForm->curveSerie->Clear();
	MainForm->curveSerie->BeginUpdate();
	for (Double i = initVal; i <= maxValPlate+step; i += step)
	{
		Double y = a * std::log(i) + b;

		MainForm->curveSerie->AddXY(i, y);
	}
	MainForm->curveSerie->EndUpdate();

	// Plotar os pontos dos padrões

    MainForm->pointsSerie->Clear();
	MainForm->pointsSerie->BeginUpdate();
	for (DoubleArray::size_type i = 0; i < arrStd.size(); i++)
	{
		Double y = arrAbs[i];
		Double x = arrStd[i];

		MainForm->pointsSerie->AddXY(x, y);

        if (!MainForm->mCurveImported)
            refCalibrationCurve.stdValues.push_back(std::pair<Double, Double>(x, y));
	}
	MainForm->pointsSerie->EndUpdate();

	String r2Text = Format(TEXT("R2 = %5.3f"), ARRAYOFCONST((FitQual)));

	MainForm->lbR2->Caption = r2Text;

	String subTitleText = Format(TEXT("y = %5.3f * ln(x) + %5.3f"), ARRAYOFCONST((a, b)));
	MainForm->stdCurveChart->SubTitle->Text->SetText(subTitleText.c_str());

    refCalibrationCurve.qtdParameters = 2;
	refCalibrationCurve.parameters.push_back(a);
    refCalibrationCurve.parameters.push_back(b);

    refCalibrationCurve.timestamp = Now();

	if (!MainForm->mCurveImported)
        refCalibrationCurve.timestamp = Now();

	return True;
}

Boolean __fastcall TMyDataModule::CalcQuadraticCurveFit(CalibrationData& refCalibrationCurve)
{
	using System::Sysutils::Format;

    WellMatrixList& wellMatrixListRef = (*TWellMatrixSingleton::instance());

	DoubleArray arrStd, arrAbs, arrConc;
	Double r2 = 0;

	WellList conclp;
    wellMatrixListRef.front().filterWellsByType(TWellType::wlConcentrationStd, conclp);

	curveFit->Init();

    if (!MainForm->mCurveImported)
    {
        if (conclp.empty())
            return True;

		std::sort(conclp.begin(), conclp.end());

		WellList::iterator last = std::unique(conclp.begin(), conclp.end());

		WellList::size_type unElements = std::distance(conclp.begin(), last);
		conclp.resize(unElements);

		for (WellList::const_iterator it = conclp.begin(); it != conclp.end(); ++it)
		{
			WellListPointers wlp = wellMatrixListRef.front().getAllReplicas(*it);

			Double accRawBlankReduced = 0;

			for (WellListPointers::const_iterator cit = wlp.begin(); cit != wlp.end(); cit++)
				accRawBlankReduced += (*cit)->RawBlankReducedValue;

			Double avgRawBlankReduced = accRawBlankReduced / std::max<Double>(wlp.size(), 0.000001);

			for (WellListPointers::iterator wit = wlp.begin(); wit != wlp.end(); wit++)
				(*wit)->RawBlankReducedValue = avgRawBlankReduced;
		}

		for (WellList::const_iterator it = conclp.begin(); it != conclp.end(); ++it)
		{
			arrAbs.push_back(it->RawBlankReducedValue);
			arrStd.push_back(it->StdValue);
		}
	}
	else
	{
		std::vector< std::pair<Double, Double> >::const_iterator it;
		for (it = refCalibrationCurve.stdValues.begin(); it != refCalibrationCurve.stdValues.end(); it++)
		{
			arrAbs.push_back(it->first);
			arrStd.push_back(it->second);
		}
	}

	for (DoubleArray::size_type i = 0; i < arrStd.size(); i++)
	{
		Double x = arrAbs[i];
		Double y = arrStd[i];

		curveFit->EnterStatValue(x, y);
	}

	Double a = 0, b = 0, c = 0, FitQual = 0;

	Boolean nearSingular = False;
	std::unique_ptr<Double> kArray(new Double[3]);

	// Obtemos a equação da curva
	try
	{
		curveFit->CalcPolyFit(2, kArray.get(), 3, FitQual, nearSingular);
	}
	catch (const Exception& e)
	{
		MessageDlg(e.Message, mtError, TMsgDlgButtons() << mbOK, 0);

		return False;
	}

	a = kArray.get()[2];
	b = kArray.get()[1];
	c = kArray.get()[0];

	// Aplica o cálculo da concentração a todas a células diferentes de Vazio.
	for (WellMatrixList::size_type i = 0; i < wellMatrixListRef.size(); i++)
	{
		TWellMatrix& refMatrix = wellMatrixListRef[i];

		for (Integer row = 0; row < MainForm->m_elisaDeviceParams->PlateRows; row++)
		{
			for (WellList::iterator it = refMatrix[row].begin(); it != refMatrix[row].end(); it++)
			{
				if (it->Type == TWellType::wlEmpty)
					continue;

				Double v = a * std::pow(it->RawBlankReducedValue, 2) +
						   b * it->RawBlankReducedValue + c;
				it->ConcentrationValue = std::max(0.0, v);
			}
		}
	}

	for (WellList::const_iterator it = conclp.begin(); it != conclp.end(); ++it)
	{
		WellListPointers wlp = wellMatrixListRef.front().getAllReplicas(*it);

		Double accConc = 0;

		for (WellListPointers::const_iterator cit = wlp.begin(); cit != wlp.end(); cit++)
			accConc += (*cit)->ConcentrationValue;

		Double avgConc = accConc / std::max<Double>(wlp.size(), 0.000001);

		for (WellListPointers::iterator wit = wlp.begin(); wit != wlp.end(); wit++)
			(*wit)->ConcentrationValue = avgConc;
	}

	curveFit->Init();

	for (DoubleArray::size_type i = 0; i < arrStd.size(); i++)
	{
		Double x = arrStd[i];
		Double y = arrAbs[i];

		curveFit->EnterStatValue(x, y);
	}

	a = 0;
	b = 0;
	c = 0;
	FitQual = 0;

	kArray.reset(new Double[3]);

	// Obtemos a equação da curva
	try
	{
		curveFit->CalcPolyFit(2, kArray.get(), 3, FitQual, nearSingular);
	}
	catch (const Exception& e)
	{
		TaskMessageDlg(TEXT("Atenção"),
					   TEXT("Para uma calibração com curva Logarítmica, os valores devem ser positivos."),
					   mtError,
					   TMsgDlgButtons() << mbOK, 0);

		return False;
	}

	a = kArray.get()[2];
	b = kArray.get()[1];
	c = kArray.get()[0];

	// Varre a placa para isolar o valor máximo.
	Double maxValPlate = 0;

	for (WellMatrixList::size_type i = 0; i < wellMatrixListRef.size(); i++)
	{
        TWellMatrix& refMatrix = wellMatrixListRef[i];

		for (Integer row = 0; row < MainForm->m_elisaDeviceParams->PlateRows; row++)
		{
			for (WellList::iterator it = refMatrix[row].begin(); it != refMatrix[row].end(); it++)
			{
				if (it->Type == TWellType::wlEmpty)
					continue;

				maxValPlate = std::max(maxValPlate, std::max(it->StdValue, it->ConcentrationValue));
			}
		}
	}

	// Determinar o "step" do gráfico.
	Double step = maxValPlate / StepResolution;
	Double maxValue = std::max<Double>(*std::max_element(arrAbs.begin(), arrAbs.end()), 0);
	Double minValue = *std::min_element(arrAbs.begin(), arrAbs.end());

	MainForm->stdCurveChart->LeftAxis->Maximum = maxValue;
	MainForm->stdCurveChart->LeftAxis->Minimum = std::min(minValue, maxValue);

	MainForm->stdCurveChart->BottomAxis->Minimum = 0;
	MainForm->stdCurveChart->BottomAxis->Maximum = std::max<Double>(maxValPlate, 0);
	MainForm->stdCurveChart->BottomAxis->Increment = (Double)((Integer)maxValPlate / 10.0);

	MainForm->curveSerie->Clear();
	MainForm->curveSerie->BeginUpdate();
	for (Double x = minValue; x <= maxValPlate; x += step)
	{
		Double y = a * std::pow(x, 2) + b * x + c;

		MainForm->curveSerie->AddXY(x, y);
	}
	MainForm->curveSerie->EndUpdate();

	// Plotar os pontos dos padrões

    MainForm->pointsSerie->Clear();
	MainForm->pointsSerie->BeginUpdate();
	for (DoubleArray::size_type i = 0; i < arrStd.size(); i++)
	{
		Double x = arrStd[i];
		Double y = arrAbs[i];

		MainForm->pointsSerie->AddXY(x, y);

        if (!MainForm->mCurveImported)
            refCalibrationCurve.stdValues.push_back(std::pair<Double, Double>(x, y));
	}
	MainForm->pointsSerie->EndUpdate();

	String r2Text = Format(TEXT("R2 = %5.3f"), ARRAYOFCONST((FitQual)));

	MainForm->lbR2->Caption = r2Text;

    String subtitleText = Format(_T("y = %5.3fx² + %5.3fx + %5.3f"), ARRAYOFCONST((a, b, c)));
	MainForm->stdCurveChart->SubTitle->Text->SetText(subtitleText.c_str());

	refCalibrationCurve.qtdParameters = 3;
    refCalibrationCurve.parameters.push_back(a);
    refCalibrationCurve.parameters.push_back(b);
	refCalibrationCurve.parameters.push_back(c);

    refCalibrationCurve.timestamp = Now();

    if (!MainForm->mCurveImported)
        refCalibrationCurve.timestamp = Now();

	return True;
}

Boolean __fastcall TMyDataModule::CalcCubicSplineCurveFit(CalibrationData& refCalibrationCurve)
{
	using System::Sysutils::Format;

	WellMatrixList& wellMatrixListRef = (*TWellMatrixSingleton::instance());
	DoubleArray arrStd, arrAbs, arrConc;
	Double r2 = 0;

	WellList conclp;
    wellMatrixListRef.front().filterWellsByType(TWellType::wlConcentrationStd, conclp);

	curveFit->Init();

    if (!MainForm->mCurveImported)
    {
        if (conclp.empty())
            return True;

		std::sort(conclp.begin(), conclp.end());

		WellList::iterator last = std::unique(conclp.begin(), conclp.end());

		WellList::size_type unElements = std::distance(conclp.begin(), last);
		conclp.resize(unElements);

		for (WellList::const_iterator it = conclp.begin(); it != conclp.end(); ++it)
		{
			WellListPointers wlp = wellMatrixListRef.front().getAllReplicas(*it);

			Double accRawBlankReduced = 0;

			for (WellListPointers::const_iterator cit = wlp.begin(); cit != wlp.end(); cit++)
				accRawBlankReduced += (*cit)->RawBlankReducedValue;

			Double avgRawBlankReduced = accRawBlankReduced / std::max<Double>(wlp.size(), 0.000001);

			for (WellListPointers::iterator wit = wlp.begin(); wit != wlp.end(); wit++)
				(*wit)->RawBlankReducedValue = avgRawBlankReduced;
		}

		for (WellList::const_iterator it = conclp.begin(); it != conclp.end(); ++it)
		{
			arrAbs.push_back(it->RawBlankReducedValue);
			arrStd.push_back(it->StdValue);
		}
	}
	else
	{
		std::vector< std::pair<Double, Double> >::const_iterator it;
		for (it = refCalibrationCurve.stdValues.begin(); it != refCalibrationCurve.stdValues.end(); it++)
		{
			arrAbs.push_back(it->first);
			arrStd.push_back(it->second);
		}
	}

	for (DoubleArray::size_type i = 0; i < arrStd.size(); i++)
	{
		Double x = arrAbs[i];
		Double y = arrStd[i];

		curveFit->EnterStatValue(x, y);
	}

	Double a = 0, b = 0, c = 0, d = 0, FitQual = 0;

	Boolean nearSingular = False;
	std::unique_ptr<Double> kArray(new Double[4]);

	// Obtemos a equação da curva
	try
	{
		curveFit->CalcPolyFit(3, kArray.get(), 4, FitQual, nearSingular);
	}
	catch (const Exception& e)
	{
		MessageDlg(e.Message, mtError, TMsgDlgButtons() << mbOK, 0);

		return False;
	}

	a = kArray.get()[3];
	b = kArray.get()[2];
	c = kArray.get()[1];
	d = kArray.get()[0];

	// Aplica o cálculo da concentração a todas a células diferentes de Vazio.
	for (WellMatrixList::size_type i = 0; i < wellMatrixListRef.size(); i++)
	{
		TWellMatrix& refMatrix = wellMatrixListRef[i];

		for (Integer row = 0; row < MainForm->m_elisaDeviceParams->PlateRows; row++)
		{
			for (WellList::iterator it = refMatrix[row].begin(); it != refMatrix[row].end(); it++)
			{
				if (it->Type == TWellType::wlEmpty)
					continue;

				Double v = a * std::pow(it->RawBlankReducedValue, 3) +
						   b * std::pow(it->RawBlankReducedValue, 2) +
						   c * it->RawBlankReducedValue + d;
				it->ConcentrationValue = v;
			}
		}
	}

	for (WellList::const_iterator it = conclp.begin(); it != conclp.end(); ++it)
	{
		WellListPointers wlp = wellMatrixListRef.front().getAllReplicas(*it);

		Double accConc = 0;

		for (WellListPointers::const_iterator cit = wlp.begin(); cit != wlp.end(); cit++)
			accConc += (*cit)->ConcentrationValue;

		Double avgConc = accConc / std::max<Double>(wlp.size(), 0.000001);

		for (WellListPointers::iterator wit = wlp.begin(); wit != wlp.end(); wit++)
			(*wit)->ConcentrationValue = avgConc;
	}

	curveFit->Init();

	for (DoubleArray::size_type i = 0; i < arrStd.size(); i++)
	{
		Double x = arrStd[i];
		Double y = arrAbs[i];

		curveFit->EnterStatValue(x, y);
	}

	a = 0;
	b = 0;
	c = 0;
	d = 0;
	FitQual = 0;

	kArray.reset(new Double[3+1]);

	// Obtemos a equação da curva
	try
	{
		curveFit->CalcPolyFit(3, kArray.get(), 4, FitQual, nearSingular);
	}
	catch (const Exception& e)
	{
		TaskMessageDlg(TEXT("Atenção"),
					   TEXT("Para uma calibração com curva Logarítmica, os valores devem ser positivos."),
					   mtError,
					   TMsgDlgButtons() << mbOK, 0);

		return False;
	}

	a = kArray.get()[3];
	b = kArray.get()[2];
	c = kArray.get()[1];
	d = kArray.get()[0];

	// Varre a placa para isolar o valor máximo.
	Double maxValPlate = 0;

	for (WellMatrixList::size_type i = 0; i < wellMatrixListRef.size(); i++)
	{
		TWellMatrix& refMatrix = wellMatrixListRef[i];

		for (Integer row = 0; row < MainForm->m_elisaDeviceParams->PlateRows; row++)
		{
			for (WellList::iterator it = refMatrix[row].begin(); it != refMatrix[row].end(); it++)
			{
				if (it->Type == TWellType::wlEmpty)
					continue;

				maxValPlate = std::max(maxValPlate, std::max(it->StdValue, it->ConcentrationValue));
			}
		}
	}

	// Determinar o "step" do gráfico.
	Double step = maxValPlate / StepResolution;
	Double maxValue = std::max<Double>(*std::max_element(arrAbs.begin(), arrAbs.end()), 0);
	Double minValue = *std::min_element(arrAbs.begin(), arrAbs.end());

	MainForm->stdCurveChart->LeftAxis->Maximum = maxValue;
	MainForm->stdCurveChart->LeftAxis->Minimum = std::min(minValue, maxValue);

	MainForm->stdCurveChart->BottomAxis->Minimum = 0;
	MainForm->stdCurveChart->BottomAxis->Maximum = std::max<Double>(maxValPlate, 0);
	MainForm->stdCurveChart->BottomAxis->Increment = (Double)((Integer)maxValPlate / 10.0);

	MainForm->curveSerie->Clear();
	MainForm->curveSerie->BeginUpdate();
	for (Double x = minValue; x <= maxValPlate; x += step)
	{
		Double y = a * std::pow(x, 3) + b * std::pow(x, 2) + c * x + d;

		MainForm->curveSerie->AddXY(x, y);
	}
	MainForm->curveSerie->EndUpdate();

	// Plotar os pontos dos padrões

	MainForm->pointsSerie->Clear();
	MainForm->pointsSerie->BeginUpdate();
	for (DoubleArray::size_type i = 0; i < arrStd.size(); i++)
	{
		Double x = arrStd[i];
		Double y = arrAbs[i];

		MainForm->pointsSerie->AddXY(x, y);

        if (!MainForm->mCurveImported)
            refCalibrationCurve.stdValues.push_back(std::pair<Double, Double>(x, y));
	}
	MainForm->pointsSerie->EndUpdate();

	String r2Text = Format(TEXT("R2 = %5.3f"), ARRAYOFCONST((FitQual)));

	MainForm->lbR2->Caption = r2Text;

	String subtitleText;
	subtitleText.sprintf(TEXT("y = %5.3fx³ + %5.3fx² + %5.3fx + %5.3f"), a, b, c, d);

	MainForm->stdCurveChart->SubTitle->Text->SetText(subtitleText.c_str());

    refCalibrationCurve.qtdParameters = 4;
    refCalibrationCurve.parameters.push_back(a);
    refCalibrationCurve.parameters.push_back(b);
    refCalibrationCurve.parameters.push_back(c);
    refCalibrationCurve.parameters.push_back(d);

    refCalibrationCurve.timestamp = Now();

    if (!MainForm->mCurveImported)
        refCalibrationCurve.timestamp = Now();

	return True;
}

Boolean __fastcall TMyDataModule::CalcLogitLogCurveFit(CalibrationData&)
{
/*
	WellListPointers conclp = wellMatrixList[0]->filterWellsPointersByType(TWellType::wlConcentrationStd);
	if (conclp.empty())
		return True;

	for (WellListPointers::iterator it = conclp.begin(); it != conclp.end(); it++)
	{
		TWell *w = (*it);

		arrAbs.push_back(w->RawValue);
		arrStd.push_back(w->StdValue);
	}

	curveFit->Init();

	for (DoubleArray::size_type i = 0; i < arrStd.size(); i++)
	{
		Double x = arrAbs[i];
		Double y = arrStd[i];

		curveFit->EnterStatValue(x, y);
	}

	Double a = 0, b = 0, FitQual = 0;

	// Obtemos a equação da curva
	try
	{
		curveFit->CalcLogFit(a, b, FitQual);
	}
	catch (const Exception& e)
	{
		MessageDlg(e.Message, mtError, TMsgDlgButtons() << mbOK, 0);

		return False;
	}

	// Varre a placa para isolar o valor máximo.
	Double maxValPlate = 0;

	for (it = wellMatrixList.begin(); it != wellMatrixList.end(); it++)
	{
		for (Integer row = 0; row < lmr96Params->PlateRows; row++)
		{
			for (Integer col = 0; col < lmr96Params->PlateCols; col++)
			{
				TWellMatrixPt matrix = (*it);
				TWell& w = (*matrix)(row, col);

				if (w.Type == TWellType::wlEmpty)
					continue;

				maxValPlate = std::max(maxValPlate, std::max(w.StdValue, w.ConcentrationValue));
			}
		}
	}

	// Determinar o "step" do gráfico.
	Double step = maxValPlate / StepResolution;

	stdCurveChart->LeftAxis->Maximum = arrAbs.back();
	stdCurveChart->LeftAxis->Minimum = 0;
	stdCurveChart->BottomAxis->Maximum = maxValPlate;
	stdCurveChart->BottomAxis->Minimum = 0;

	// Aplica o cálculo da concentração a todas a células diferentes de Vazio.
	for (Integer row = 0; row < lmr96Params->PlateRows; row++)
	{
		for (Integer col = 0; col < lmr96Params->PlateCols; col++)
		{
			TWell& w = (*matrix)(row, col);

			if (w.Type == TWellType::wlEmpty)
				continue;

			Double v = (w.RawBlankReducedValue - a) / b;
			w.ConcentrationValue = v;
		}
	}

	for (Double x = 0; x <= maxValPlate; x += step)
	{
		Double y = a * std::pow(x, 2) + b * x + c;

		if (0.0 > y)
			continue;

		curveSerie->AddXY(x, y);
	}
	curveSerie->EndUpdate();

	curveSerie->BeginUpdate();
	for (Double y = minValue; y < maxValue; y += step)
	{
		Double x = std::pow(10, (y - k0) / k1);

		if (0.0 > x)
			continue;

		curveSerie->AddXY(x, y);
	}
	curveSerie->EndUpdate();

	// Plotar os pontos dos padrões

	pointsSerie->BeginUpdate();
	for (DoubleArray::size_type i = 0; i < arrAbs.size(); i++)
	{
		Double x = arrStd[i];
		Double y = arrAbs[i];

		pointsSerie->AddXY(x, y);
	}
	pointsSerie->EndUpdate();

	String r2Text = Format(_T("R2 = %5.3f"), ARRAYOFCONST((FitQual)));

	lbR2->Caption = r2Text;

	stdCurveChart->SubTitle->Text->SetText(Format(_T("y = %5.3f * Log(x) + %5.3f"), ARRAYOFCONST((k1, k0))).c_str());
*/
	return True;
}

Boolean __fastcall TMyDataModule::Calc4ParametersCurveFit(CalibrationData&)
{
/*	using System::Sysutils::Format;

	DoubleArray arrStd, arrAbs, arrUnknowns, arrConc;
	Double r2 = 0;

	WellListPointers conclp = matrix->filterWellsPointersByType(TWellType::wlConcentrationStd);
	if (conclp.empty())
		return True;

	for (WellListPointers::iterator it = conclp.begin(); it != conclp.end(); it++)
	{
		TWell *w = (*it);

		arrAbs.push_back(w->RawValue);
		arrStd.push_back(w->StdValue);
	}

	WellListPointers ulp = matrix->filterWellsPointersByType(TWellType::wlUnknown);
	if (ulp.empty())
		return True;

	for (WellListPointers::iterator it = ulp.begin(); it != ulp.end(); it++)
		arrUnknowns.push_back((*it)->RawValue);

	curveFit->Init();

	pointsSerie->Clear();
	curveSerie->Clear();

	for (DoubleArray::size_type i = 0; i < arrStd.size(); i++)
	{
		Double x = arrStd[i];
		Double y = arrAbs[i];

		curveFit->EnterStatValue(x, y);
	}

	Double k0 = 0, k1 = 0, FitQual = 0;

	// Obtemos a equação da curva
	try
	{
		curveFit->CalcLogFit(k0, k1, FitQual);
	}
	catch (const Exception& e)
	{
		MessageDlg(e.Message, mtError, TMsgDlgButtons() << mbOK, 0);

		return False;
	}

	// Aplica o cálculo da concentração a todas a células diferentes de Vazio.
	for (Integer row = 0; row < lmr96Params->PlateRows; row++)
	{
		for (Integer col = 0; col < lmr96Params->PlateCols; col++)
		{
			TWell& w = (*matrix)(row, col);

			if (w.Type == TWellType::wlEmpty)
				continue;

			Double v = (w.RawBlankReducedValue - k0) / k1;
			w.ConcentrationValue = v;
		}
	}

	// Obtemos o range do gráfico a ser plotado
	Double maxValue = std::max(*std::max_element(arrAbs.begin(), arrAbs.end()),
							   *std::max_element(arrUnknowns.begin(), arrUnknowns.end()));

	Double minValue = 0;

	minValue = std::min(*std::min_element(arrAbs.begin(), arrAbs.end()),
						*std::min_element(arrUnknowns.begin(), arrUnknowns.end()));

	// Determinar o "step" do gráfico.
	Double step = (maxValue - minValue) / StepResolution;

	// Determina-se o array de plot da curva;
	pointsSerie->BeginUpdate();
	curveSerie->BeginUpdate();

	minValue = 0;

	for (Double y = minValue; y < maxValue; y += step)
	{
		Double x = std::pow(10, (y - k0) / k1);

		if (0.0 > x)
			continue;

		curveSerie->AddXY(x, y);
	}

	// Plotar os pontos dos padrões

	for (DoubleArray::size_type i = 0; i < arrAbs.size(); i++)
	{
		Double x = arrStd[i];
		Double y = arrAbs[i];

		pointsSerie->AddXY(x, y);
	}

	pointsSerie->EndUpdate();
	curveSerie->EndUpdate();

	String r2Text = System::Sysutils::Format(_T("R2 = %5.3f"), ARRAYOFCONST((FitQual)));

	lbR2->Caption = r2Text;

	stdCurveChart->SubTitle->Text->SetText(Format(_T("y = %5.3f * Log(x) + %5.3f"), ARRAYOFCONST((k1, k0))).c_str());
*/
	return True;
}

Boolean __fastcall TMyDataModule::Calc5ParametersCurveFit(CalibrationData&)
{
/*	using System::Sysutils::Format;

	DoubleArray arrStd, arrAbs, arrUnknowns, arrConc;
	Double r2 = 0;

	WellListPointers conclp = matrix->filterWellsPointersByType(TWellType::wlConcentrationStd);
	if (conclp.empty())
		return True;

	for (WellListPointers::iterator it = conclp.begin(); it != conclp.end(); it++)
	{
		TWell *w = (*it);

		arrAbs.push_back(w->RawValue);
		arrStd.push_back(w->StdValue);
	}

	WellListPointers ulp = matrix->filterWellsPointersByType(TWellType::wlUnknown);
	if (ulp.empty())
		return True;

	for (WellListPointers::iterator it = ulp.begin(); it != ulp.end(); it++)
		arrUnknowns.push_back((*it)->RawValue);

	curveFit->Init();

	pointsSerie->Clear();
	curveSerie->Clear();

	for (DoubleArray::size_type i = 0; i < arrStd.size(); i++)
	{
		Double x = arrStd[i];
		Double y = arrAbs[i];

		curveFit->EnterStatValue(x, y);
	}

	Double k0 = 0, k1 = 0, FitQual = 0;

	// Obtemos a equação da curva
	try
	{
		curveFit->CalcLogFit(k0, k1, FitQual);
	}
	catch (const Exception& e)
	{
		MessageDlg(e.Message, mtError, TMsgDlgButtons() << mbOK, 0);

		return False;
	}

	// Aplica o cálculo da concentração a todas a células diferentes de Vazio.
	for (Integer row = 0; row < lmr96Params->PlateRows; row++)
	{
		for (Integer col = 0; col < lmr96Params->PlateCols; col++)
		{
			TWell& w = (*matrix)(row, col);

			if (w.Type == TWellType::wlEmpty)
				continue;

			Double v = (w.RawBlankReducedValue - k0) / k1;
			w.ConcentrationValue = v;
		}
	}

	// Obtemos o range do gráfico a ser plotado
	Double maxValue = std::max(*std::max_element(arrAbs.begin(), arrAbs.end()),
							   *std::max_element(arrUnknowns.begin(), arrUnknowns.end()));

	Double minValue = 0;

	minValue = std::min(*std::min_element(arrAbs.begin(), arrAbs.end()),
						*std::min_element(arrUnknowns.begin(), arrUnknowns.end()));

	// Determinar o "step" do gráfico.
	Double step = (maxValue - minValue) / StepResolution;

	// Determina-se o array de plot da curva;
	pointsSerie->BeginUpdate();
	curveSerie->BeginUpdate();

	minValue = 0;

	for (Double y = minValue; y < maxValue; y += step)
	{
		Double x = std::pow(10, (y - k0) / k1);

		if (0.0 > x)
			continue;

		curveSerie->AddXY(x, y);
	}

	// Plotar os pontos dos padrões

	for (DoubleArray::size_type i = 0; i < arrAbs.size(); i++)
	{
		Double x = arrStd[i];
		Double y = arrAbs[i];

		pointsSerie->AddXY(x, y);
	}

	pointsSerie->EndUpdate();
	curveSerie->EndUpdate();

	String r2Text = Format(_T("R2 = %5.3f"), ARRAYOFCONST((FitQual)));

	lbR2->Caption = r2Text;

	stdCurveChart->SubTitle->Text->SetText(Format(_T("y = %5.3f * Log(x) + %5.3f"), ARRAYOFCONST((k1, k0))).c_str());
*/
	return True;
}

Boolean __fastcall TMyDataModule::CalcPointToPointCurveFit(CalibrationData&)
{
/*	using System::Sysutils::Format;

	DoubleArray arrStd, arrAbs, arrUnknowns, arrConc;
	Double r2 = 0;

	WellListPointers conclp = matrix->filterWellsPointersByType(TWellType::wlConcentrationStd);
	if (conclp.empty())
		return True;

	for (WellListPointers::iterator it = conclp.begin(); it != conclp.end(); it++)
	{
		TWell *w = (*it);

		arrAbs.push_back(w->RawValue);
		arrStd.push_back(w->StdValue);
	}

	WellListPointers ulp = matrix->filterWellsPointersByType(TWellType::wlUnknown);
	if (ulp.empty())
		return True;

	for (WellListPointers::iterator it = ulp.begin(); it != ulp.end(); it++)
		arrUnknowns.push_back((*it)->RawValue);

	curveFit->Init();

	curveFit->EnterStatValue(0, 0);

	Double k = 0, d = 0, FitQual = 0;

	try
	{
		curveFit->CalcLinFit(k, d, FitQual);
	}
	catch (const Exception& e)
	{
		MessageDlg(e.Message, mtError, TMsgDlgButtons() << mbOK, 0);

		return False;
	}

	// Aplica o cálculo da concentração a todas a células diferentes de Vazio.
	for (Integer row = 0; row < lmr96Params->PlateRows; row++)
	{
		for (Integer col = 0; col < lmr96Params->PlateCols; col++)
		{
			TWell& w = (*matrix)(row, col);

			if (w.Type == TWellType::wlEmpty)
				continue;

			Double v = (w.RawBlankReducedValue - d) / k;
			w.ConcentrationValue = v;
		}
	}

	TChartSeries *serieLine = stdCurveChart->Series[0];
	TChartSeries *pointsSerie = stdCurveChart->Series[1];

	pointsSerie->Clear();
	serieLine->Clear();
	serieLine->BeginUpdate();

	serieLine->AddXY(0, 0);
	pointsSerie->AddXY(0, 0);

	for (DoubleArray::size_type i = 1; i < arrAbs.size()+1; i++)
		pointsSerie->AddXY(arrAbs[i], arrStd[i]);

	Double maxXValue = std::max(*std::max_element(arrAbs.begin(), arrAbs.end()),
								*std::max_element(arrUnknowns.begin(), arrUnknowns.end()));

	for (DoubleArray::size_type i = 0; i < ulp.size(); i++)
		serieLine->AddXY(maxXValue, maxXValue * k + d);

	serieLine->EndUpdate();

	String title = Format(_T("%s (R2: %5.3f)"),
						  ARRAYOFCONST((stdCurveChart->Title->Text->GetText(), FitQual)));

	stdCurveChart->Title->Text->SetText(title.c_str());
*/
	return True;
}

String __fastcall TMyDataModule::EncryptString(const String& decrypted)
{
	return IdEncoderUUE->EncodeString(decrypted);
}

Boolean __fastcall TMyDataModule::CreateDirectoryRecursively(const String& dirPath)
{
	if (DirectoryExists(dirPath, False))
		return True;

	Integer pos = dirPath.LastDelimiter(DirSeparators);

	if (pos > 0)
		CreateDirectoryRecursively(dirPath.SubString(1, pos - 1));

	return CreateDir(dirPath);
}

