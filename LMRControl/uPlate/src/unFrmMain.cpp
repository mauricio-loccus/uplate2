//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.SysUtils.hpp>
#include <System.IOUtils.hpp>
#include <System.Math.hpp>

#include <dbt.h>
#include <setupapi.h>

#include <io.h>
#include <WinIOCTL.h>
#include <devguid.h>

#include <Sysutils.hpp>

#include <iomanip>
#include <string>
#include <numeric>
#include <algorithm>
#include <memory>
#include <utility>
#include <iterator>
#include <cmath>
#include <limits>

#include <exception>

#pragma hdrstop

#include "unFrmMain.h"
#include "unDataModule.h"
#include "unDBModule.h"
#include "unInputFloatValue.h"
#include "unRenamePlate.h"
#include "unFrmWait.h"
#include "unKineticControler.h"
#include "unFrmFiltersEdit.h"
#include "unFrmSplash.h"
#include "unFrmAppLogin.h"
#include "unFrmProtocol.h"
#include "unDataModule.h"
#include "unFrmConfig.h"
#include "unFrmAbout.h"
#include "unFileFilters.h"
#include "unFrmLabelAssign.h"

#include "unDeviceFactory.h"
#include "unLMR96Device.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LMDControl"
#pragma link "LMDCustomControl"
#pragma link "LMDCustomPanel"
#pragma link "LMDCustomSheetControl"
#pragma link "LMDPageControl"
#pragma link "LMDBaseControl"
#pragma link "LMDBaseGraphicControl"
#pragma link "LMDBaseImage"
#pragma link "LMDCustomNImage"
#pragma link "LMDGraphicControl"
#pragma link "LMDNImage"
#pragma link "LMDCustomBevelPanel"
#pragma link "LMDCustomPanelFill"
#pragma link "LMDCustomParentPanel"
#pragma link "LMDCustomComponent"
#pragma link "LMDCustomHint"
#pragma link "LMDCustomShapeHint"
#pragma link "LMDMessageHint"
#pragma link "LMDNativeHint"
#pragma link "LMDButtonControl"
#pragma link "LMDCheckBox"
#pragma link "LMDCustomCheckBox"
#pragma link "LMDGrid"
#pragma link "LMDShapeHint"
#pragma link "frxClass"
#pragma link "frxExportPDF"

#pragma link "SDL_math2"
#pragma link "MathEvaluator.lib"

#pragma link "LMDBaseGraphicButton"
#pragma link "LMDCustomMMButton"
#pragma link "LMDMMButton"
#pragma link "LMDCustomScrollBox"
#pragma link "LMDListBox"
#pragma link "LMDBaseEdit"
#pragma link "LMDCustomEdit"
#pragma link "LMDCustomExtSpinEdit"
#pragma link "LMDCustomMaskEdit"
#pragma link "LMDSpinEdit"
#pragma link "LMDMaskEdit"
#pragma link "LMDFloatRangeValidator"
#pragma link "LMDHintErrorProvider"
#pragma link "LMDVldBase"
#pragma link "LMDScrollBox"
#pragma link "LMDCheckGroup"
#pragma link "LMDCustomButtonGroup"
#pragma link "LMDCustomCheckGroup"
#pragma link "LMDCustomGroupBox"
#pragma link "LMDButtonPanel"
#pragma link "LMDCustomToolBar"
#pragma link "LMDToolBar"
#pragma link "LMDTaskDlg"
#pragma link "frxExportBaseDialog"

#pragma link "Vcl.Dialogs"
#pragma link "Vcl.FileCtrl"
#pragma link "Vcl.StdCtrls"
#pragma link "Vcl.Controls"
#pragma link "Vcl.Forms"
#pragma link "Vcl.ExtCtrls"
#pragma link "Vcl.Graphics"
#pragma link "Vcl.Imaging.jpeg"
#pragma link "Vcl.Menus"
#pragma link "Vcl.ComCtrls"
#pragma link "Vcl.Grids"
#pragma link "Vcl.Samples.Spin"
#pragma link "Vcl.Mask"
#pragma link "Vcl.Buttons"
#pragma link "Vcl.CheckLst"
#pragma link "Vcl.DBCtrls"
#pragma link "Vcl.DBGrids"
#pragma link "Vcl.ToolWin"
#pragma link "Vcl.ActnList"
#pragma link "Vcl.StdActns"
#pragma link "Vcl.PlatformDefaultStyleActnCtrls"

#pragma resource "*.dfm"

#define APPMUTEXNAME TEXT("LMR96.0")

TMainForm *MainForm = NULL;

HANDLE TMainForm::singletonEventHandle = INVALID_HANDLE_VALUE;

Boolean __fastcall StringToTime(const String& sTime, TTime& t)
{
	uint16_t hh = 0, mm = 0, ss = 0;

	std::unique_ptr<TRegEx> reg(new TRegEx(_T("(([0-1]?\\d|2[0-3]):)?([0-5]?\\d):([0-5]?\\d)"), TRegExOptions()));

	TMatchCollection mc = reg->Matches(sTime);

	if (!mc.Count || !mc[0].Groups.Count)
		return False;

	for (Integer i = 0; i < mc.Count; i++)
	{
		for (Integer j = 0; j < mc[i].Groups.Count; j++)
		{
			switch (j)
			{
				case 2:
					if (!mc[i].Groups[j].Value.IsEmpty())
						hh = mc[i].Groups[j].Value.ToInt();

					break;

				case 3:
					mm = mc[i].Groups[j].Value.ToInt();
					break;

				case 4:
					ss = mc[i].Groups[j].Value.ToInt();
					break;
			}
		}
	}

	uint16_t dhh = 0, dmm = 0, dss = 0, dms = 0;

	t = TTime(hh, mm, ss, 0);

	DecodeTime(t, dhh, dmm, dss, dms);

	if ((hh != dhh) ||(mm != dmm) | (ss != dss))
		return False;

	return True;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::LoginRequest()
{
	this->UserLogon();
}

//---------------------------------------------------------------------------

 Boolean __fastcall TMainForm::UserLogon()
{
	StatusBar->Panels->BeginUpdate();
	StatusBar->Panels->Items[0]->Text = "";
	StatusBar->Panels->EndUpdate();

	try
	{
		TFrmAppLogin *FrmAppLogin = new TFrmAppLogin(this);

		if (mrOk != FrmAppLogin->ShowModal())
			return False;

		mpAppConfig->UserName = FrmAppLogin->UserName;
		mpAppConfig->UserID = FrmAppLogin->UserID;
		mpAppConfig->UserLogin = FrmAppLogin->UserLogin;
		mpAppConfig->IsSuperUser = FrmAppLogin->IsSuperUser;

		SMenuExperiment->Enabled = True;
		SMenuProtocol->Enabled = True;
	}
	__finally
	{
		FrmAppLogin->Free();
		FrmAppLogin = NULL;
	}

	StatusBar->Panels->BeginUpdate();
	StatusBar->Panels->Items[0]->Text = "@" + mpAppConfig->UserName;
	StatusBar->Panels->EndUpdate();

	OptUserLogin->Enabled = False;
	OptUserLogoff->Enabled = True;

	return True;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::setDevice(PElisaDevice pDev)
{
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::WndProc(TMessage& message)
{
	ancestor::WndProc(message);

	switch (message.Msg)
	{
		case InternalMessages::WM_PLATE_ADDED:
		{
			TWellsEdit *pwe = reinterpret_cast<TWellsEdit *>(message.LParam);

			pwe->Enabled = True;
			break;
		}

		default:
			break;
	}
}
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner), currMatrix(-1),
	  m_elisaDeviceParams(ElisaParamsSingleton::instance()),
	  hDevNotify(INVALID_HANDLE_VALUE),
	  CurrentProtocol(-1),
	  controlEnabledArray(7),
	  mWaveLengthControlsAdjusted(False),
	  mFiltersControlsAdjusted(False),
	  mCurveTypes(0),
	  m_deviceSimulated(False),
	  m_editingCol(-1), m_editingRow(-1)
{
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	FrmSplash = new TFrmSplash(this);
	FrmSplash->Show();

	FrmWait = new TFrmWait(this);

	mpAppConfig = AppConfigSingleton::instance();

	pageControl->ActivePage = tabParamRead;

	controlEnabledArray[0] = True;

	for (LongWord i = 1; i < controlEnabledArray.size(); i++)
		controlEnabledArray[i] = False;

	if (!m_deviceSimulated)
		registerForDevicesMessages();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
	if (mpAppConfig->ElisaSimulated)
	{
		PElisaDevice pDev = DeviceFactorySingleton::instance()->CreateDevice(ElisaDeviceTypeEnum::ElisaDeviceLRM96Simulator);
		m_elisaDevice = pDev;

		m_deviceSimulated = True;
	}
	else if (!mpAppConfig->Version2023)
		m_elisaDevice = DeviceFactorySingleton::instance()->CreateDevice(ElisaDeviceTypeEnum::ElisaDeviceLMR96);
	else  {
		m_elisaDevice = DeviceFactorySingleton::instance()->CreateDevice(ElisaDeviceTypeEnum::ElisaDeviceLMR96_2023);
		chbReadSpeed->Visible = true;
		lblReadSpeed->Visible = true;
		//meWaitDuration->Visible = true;
		//lblWaitDuration->Visible = true;
		chbShakeMode->Visible = true;
		lblShakeMode->Visible = true;
	}

	m_elisaDevice->OnRead = TMainForm::OnLMR96ReadDone;
	m_elisaDevice->Params = m_elisaDeviceParams;

	acNewProtocolExecute(Sender);

	treeview->FullExpand();
	TTreeNode *node = treeview->Items->GetFirstNode()->getFirstChild();
	treeview->Select(node);

	FillUnitiesComboBox();

	UpdateUi(False);

	OneShotTimer->Enabled = True;

	Application->HintHidePause = 10000;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::InitAll()
{
	currMatrix = 0;
	mCurveTypes = 0;
	cbChartScale->ItemIndex = 0;
    mCurveImported = False;
	mCalibrationCurve.reset(new CalibrationData());
	lbR2->Caption = "";
//	stdCurveChart->SubTitle->Text->SetText(TEXT(""));

	lvKineticTimes->Items->Clear();

	TTreeNode *platesNode = getNode(TEXT("Placas"));

	platesNode->DeleteChildren();

	TWellsEdit *pwe = NULL;

	while (tabPlatesScrollBox->ControlCount)
	{
		pwe = reinterpret_cast<TWellsEdit *>(tabPlatesScrollBox->Controls[tabPlatesScrollBox->ControlCount-1]);
		tabPlatesScrollBox->RemoveControl(pwe);
		pwe->Free();
	}

	pwe = NULL;

	while (tabAbsorbanceScrollBox->ControlCount)
	{
		pwe = reinterpret_cast<TWellsEdit *>(tabAbsorbanceScrollBox->Controls[tabAbsorbanceScrollBox->ControlCount-1]);
		tabAbsorbanceScrollBox->RemoveControl(pwe);
		pwe->Free();
	}

	pwe = NULL;

	while (tabConcentrationScrollBox->ControlCount)
	{
		pwe = reinterpret_cast<TWellsEdit *>(tabConcentrationScrollBox->Controls[tabConcentrationScrollBox->ControlCount-1]);
		tabConcentrationScrollBox->RemoveControl(pwe);
		pwe->Free();
	}

	pwe = NULL;

	while (tabQualitativeScrollBox->ControlCount)
	{
		pwe = reinterpret_cast<TWellsEdit *>(tabQualitativeScrollBox->Controls[tabQualitativeScrollBox->ControlCount-1]);
		tabQualitativeScrollBox->RemoveControl(pwe);
		pwe->Free();
	}

	curveSerie->Clear();
	pointsSerie->Clear();

	cbOrigin->ItemIndex = 0;
	lbZone1Limit->Caption = TEXT("Limite Zona 1:");
	lbZone2Limit->Caption = TEXT("Limite Zona 2:");
	edZone1Interpret->Text = TEXT("");
	edZone1Limit->Text = TEXT("");

	edZone2Interpret->Text = TEXT("");
	edZone2Limit->Text = TEXT("");

	edZone3Interpret->Text = TEXT("");

	unknownsGrid->BeginUpdate();
	unknownsGrid->DataRowCount = 0;
	unknownsGrid->EndUpdate();

	ReadRawGrid->BeginUpdate();
	ReadRawGrid->DataRowCount = 0;
	ReadRawGrid->EndUpdate();

	WellMatrixList& wellMatrixListRef = *TWellMatrixSingleton::instance();
	wellMatrixListRef.clear();

	InitSetup();
	InitCPCNParams();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::registerForDevicesMessages()
{
	DEV_BROADCAST_DEVICEINTERFACE notificationFilter;

	ZeroMemory(&notificationFilter, sizeof(notificationFilter));
	notificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
	notificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	notificationFilter.dbcc_classguid = GUID_DEVCLASS_PORTS;

	// We want to be notified when a COM device has plugged in.
	HWND hWnd = this->WindowHandle;

	hDevNotify = RegisterDeviceNotification(hWnd, &notificationFilter, DEVICE_NOTIFY_WINDOW_HANDLE);
	if (!hDevNotify)
	{
		LPWSTR lpMsgBuf = NULL;

		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
					  FORMAT_MESSAGE_FROM_SYSTEM |
					  FORMAT_MESSAGE_IGNORE_INSERTS,
					  NULL,
					  GetLastError(),
					  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					  (LPWSTR)&lpMsgBuf,
					  0,
					  NULL);

		ShowMessageFmt(TEXT("Can't register device notification:\n%s."), ARRAYOFCONST((lpMsgBuf)));

		LocalFree(lpMsgBuf);
	}
}

void __fastcall TMainForm::OnDeviceChange(TMessage& m)
{
	// Este bloco servirá para a detecção de um device USB pluggado.
	// No caso específico, servirá para mostrar o cursor do mouse sempre que
	// for detectado o inserimento de um mouse usb.

	switch (m.WParam)
	{
		case DBT_DEVICEARRIVAL:
		{
			PDEV_BROADCAST_PORT pPort = (PDEV_BROADCAST_PORT)m.LParam;

			if (pPort && DBT_DEVTYP_PORT != pPort->dbcp_devicetype)
				return;

			StlString hwdId = GetHardwareID(pPort->dbcp_name);

			Boolean vendorOk = False;
			Word vendorId = deviceVendorIdentifier(hwdId, vendorOk);

			if (!vendorOk || ElisaVendorID != vendorId)
				break;

			Boolean productOk = False;
			Word productId = deviceProductIdentifier(hwdId, productOk);

			if (!productOk || ElisaProductID != productId)
				break;

			commName = StlString(pPort->dbcp_name);

			if (!m_elisaDevice->isConnected && UserLogged())
				actConnectExecute(this);

			break;
		}

		case DBT_DEVICEREMOVECOMPLETE:
			if (m_elisaDevice->isConnected && m_elisaDevice->Status == ElisaDeviceCommandStatus::ElisaDeviceCommand_Idle)
				m_elisaDevice->Disconnect();
			else
			{
				m_elisaDevice->Terminate();

				UpdateUi(False);

				throw Exception(TEXT("Comunicação interrompida, perda de comunicação com a leitora."));
			}

			UpdateUi(False);

			break;
	}
}

void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	QuitAppDialog->Content = TEXT("Certifique-se de que o protocolo corrente ou o experimento foram salvos.\n")
							 TEXT("Deseja realmente prosseguir?");
	QuitAppDialog->Execute();

	if (QuitAppDialog->ResultButtonId != 200)
	{
		CanClose = False;
		return;
	}

	CanClose = True;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::treeviewChange(TObject *Sender, TTreeNode *Node)
{
	TTreeNode *platesNode = NULL, *resultsNode = NULL;
	String className = Sender->ClassName();

	platesNode = getNode(TEXT("Placas"));
	resultsNode = getNode(TEXT("Resultados"));

	TTreeNode *node = treeview->Items->GetFirstNode();
	if (node == Node)
		treeview->Select(node->getFirstChild());

	if (Node->HasChildren && className == TEXT("TTreeView"))
	{
		Node = Node->getFirstChild();

		if (Node->Parent == platesNode)
		{
			Integer matrixCount = Node->SelectedIndex - (platesNode->SelectedIndex + 1);
			RemovePlateMenuItem->Enabled = Boolean(matrixCount != 0);
		}

		if (Node->Parent == resultsNode)
        {
			pageControl->ActivePage = tabResults;

			TTVChangedEvent ev = treeview->OnChange;
			treeview->OnChange = NULL;

			if (treeview->Selected == resultsNode)
				treeview->Select(resultsNode->getFirstChild());

			treeview->OnChange = ev;

			tabResultPageControl->TabIndex = Node->SelectedIndex - (resultsNode->SelectedIndex + 1);
		}

		tabPlatesScrollBox->VertScrollBar->Position = 0;

		Integer controlHeight = (15 + tabPlatesScrollBox->Controls[0]->Height);
		tabPlatesScrollBox->VertScrollBar->Position -= -(controlHeight * (tabPlatesScrollBox->ControlCount-1));

		Node->Selected = True;

		return;
	}

	if (Node->Parent == platesNode && Node->SelectedIndex > platesNode->SelectedIndex)
	{
		TNotifyEvent ev = pageControl->OnChange;
		pageControl->OnChange = NULL;
		pageControl->ActivePage = tabPlates;
		pageControl->OnChange = ev;

		Integer matrixCount = (Node->SelectedIndex - platesNode->SelectedIndex)-1;
		RemovePlateMenuItem->Enabled = Boolean(matrixCount != 0);

		const Integer controlHeight = (15 + tabPlatesScrollBox->Controls[0]->Height);

		tabPlatesScrollBox->VertScrollBar->Position = matrixCount * controlHeight;

		return;
	}

	if (Node->Parent == resultsNode && Node->SelectedIndex >= resultsNode->SelectedIndex)
	{
		TNotifyEvent ev = pageControl->OnChange;
		pageControl->OnChange = NULL;
		pageControl->ActivePage = tabResults;
		pageControl->OnChange = ev;

		tabResultPageControl->TabIndex = (Node->SelectedIndex - resultsNode->SelectedIndex)-1;

		return;
	}

	TNotifyEvent ev = pageControl->OnChange;
	pageControl->OnChange = NULL;
	pageControl->TabIndex = Node->SelectedIndex / 100;
	pageControl->OnChange = ev;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::chkbShakeClick(TObject *Sender)
{
	m_elisaDeviceParams->Shake = chkbShake->Checked;
	chbShakeIntensity->Enabled = chkbShake->Checked;
	chbShakeMode->Enabled = chkbShake->Checked;
	meShakeDuration->Enabled = chkbShake->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::UpdateUi(Boolean enabled)
{
	TTreeNode *resultsNode = getNode(_T("Resultados"));

	setNodeEnabled(resultsNode,
				   (tabAbsorbanceScrollBox->ControlCount > 0 &&
					tabConcentrationScrollBox->ControlCount > 0 &&
					tabQualitativeScrollBox->ControlCount > 0));


	tabResultPageControl->Enabled = (tabAbsorbanceScrollBox->ControlCount > 0 &&
									 tabConcentrationScrollBox->ControlCount > 0 &&
									 tabQualitativeScrollBox->ControlCount > 0);

	cbUnity->Enabled = enabled;

	toolbar->Buttons->Items[0]->Enabled = !m_elisaDevice->isConnected && UserLogged();

	for (Integer i = 1; i < toolbar->Buttons->Count; i++)
		toolbar->Buttons->Items[i]->Enabled = m_elisaDevice->isConnected && UserLogged();

	actConnect->Enabled = !m_elisaDevice->isConnected && UserLogged();
	actDisconnect->Enabled = m_elisaDevice->isConnected && UserLogged();
	actProgramRun->Enabled = m_elisaDevice->isConnected && UserLogged();
	actOpenCloseDoor->Enabled = m_elisaDevice->isConnected && UserLogged();

	if (enabled)
	{
		grpReadMode->Enabled = True;
		rbEndPoint->Enabled = True;
		rbKinetic->Enabled = True;
		grpShakeParams->Enabled = True;
		grpFilters->Enabled = True;
		lbFilter1->Enabled = True;
		cbFilter1->Enabled = True;

		treeview->Enabled = True;
		pageControl->Enabled = True;

		toolbar->Buttons->Items[0]->Enabled = False;

		for (Integer i = 1; i < toolbar->Buttons->Count; i++)
			toolbar->Buttons->Items[i]->Enabled = True;

		treeview->Enabled = True;
		pageControl->Enabled = True;

		acConfPrefs->Enabled = True;

		if (ElisaDeviceTypeEnum::ElisaDeviceLMR96 == m_elisaDevice->Type || ElisaDeviceTypeEnum::ElisaDeviceLMR96_2023 == m_elisaDevice->Type )
			acFiltersConfig->Enabled = True;

	   //	ElisaDeviceTypeEnum::ElisaDeviceLMR96_2023 == m_elisaDevice->Type

		acExperimentImportCalibration->Enabled = True;

		return;
	}

	grpReadMode->Enabled = False;
	grpShakeParams->Enabled = False;
	grpFilters->Enabled = False;
	lbFilter1->Enabled = False;
	cbFilter1->Enabled = False;

	if (!rbKinetic->Checked)
		rbEndPointClick(NULL);

	treeview->Enabled = False;

	pageControl->TabIndex = 0;
	pageControl->Enabled = False;

	acConfPrefs->Enabled = False;
	acFiltersConfig->Enabled = False;
	acExperimentImportCalibration->Enabled = False;
}

void __fastcall TMainForm::actExitExecute(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::actConnectExecute(TObject *Sender)
{
	try
	{
		if (!m_deviceSimulated)
			FrmWait->Show();

		// Escrever código para tornar o botão toggle e conectar ou desconectar o equipamento
		m_elisaDevice->Connect(AnsiString(commName.c_str()));

		if (!m_elisaDevice->isAuthenticated)
		{
			if (!m_deviceSimulated)
				FrmWait->Close();

			MessageDlg(_T("µPlate - Nenhum equipamento compatível encontrado."),
					   mtWarning, TMsgDlgButtons() << mbOK, 0);

			actConnect->Enabled = False;
			treeview->Enabled = False;
			pageControl->Enabled = False;

			return;
		}

		if (!m_elisaDevice->isConnected)
		{
			if (!m_deviceSimulated)
			FrmWait->Close();

			MessageDlg(System::Sysutils::Format(_T("Não foi possível conectar ao equipamento.\n Verifique as conexões e tente novamente"),
							  ARRAYOFCONST((AnsiString(commName.c_str())))),
					   mtError, TMsgDlgButtons() << mbOK, 0);

			return;
		}


		// Leitura de filtros
		m_elisaDevice->sendGetFilterList();

		if (ElisaDeviceTypeEnum::ElisaDeviceLMR96Flex == m_elisaDevice->Type)
		{
			PLMR96Device lmr96Device = dynamic_cast<PLMR96Device>(m_elisaDevice);

			Integer minWaveLength = 300, maxWaveLength = 800;
			AnsiString filterSet1(lmr96Device->DefaultValue.Filter_Set_1);
			AnsiString filterSet2(lmr96Device->DefaultValue.Filter_Set_2);

			if (!filterSet1.IsEmpty())
				minWaveLength = std::max<Integer>(300, filterSet1.ToInt());

			if (!filterSet2.IsEmpty())
				maxWaveLength = std::max<Integer>(800, filterSet2.ToInt());

			spLambda1->MinValue = minWaveLength;
			spLambda1->MaxValue = maxWaveLength;
			spLambda1->Value = spLambda1->MinValue;

			spLambda2->MinValue = minWaveLength;
			spLambda2->MaxValue = maxWaveLength;
			spLambda2->Value = spLambda2->MinValue;
		}

		if (ElisaDeviceTypeEnum::ElisaDeviceLMR96 == m_elisaDevice->Type || ElisaDeviceTypeEnum::ElisaDeviceLMR96_2023 == m_elisaDevice->Type )
		{
			FillFiltersComboBox();

			if (!mFiltersControlsAdjusted)
			{
				grpFilters->Visible = True;
				lbUnity->Top -= grpWaveLength->Height;
				cbUnity->Top -= grpWaveLength->Height;
				lbUnity->Visible = True;
				cbUnity->Visible = True;

				mFiltersControlsAdjusted = True;
			}
		}
		else
		{
			if (!mWaveLengthControlsAdjusted)
			{
				grpWaveLength->Top = grpFilters->Top;
				grpWaveLength->Visible = True;
				lbUnity->Top -= grpFilters->Height;
				cbUnity->Top -= grpFilters->Height;
				lbUnity->Visible = True;
				cbUnity->Visible = True;

				mWaveLengthControlsAdjusted = True;
			}
		}

		UpdateUi(UserLogged());

		if (!m_deviceSimulated)
			FrmWait->Close();
	}
	catch (Exception& e)
	{
		if (!m_deviceSimulated)
			FrmWait->Close();

		Application->ShowException(&e);
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::actDisconnectExecute(TObject *Sender)
{
	if (!m_deviceSimulated)
	{
		FrmWait->Show();

	m_elisaDevice->Disconnect();

	UpdateUi(m_elisaDevice->isConnected);

	FrmWait->Close();
	}

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::chbShakeIntensityChange(TObject *Sender)
{
	m_elisaDeviceParams->ShakeIntensity = static_cast<TElisaShakeIntensity>(chbShakeIntensity->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DoProcessBlanks()
{
	WellMatrixList& wellMatrixListRef = *TWellMatrixSingleton::instance();

	Double blankAvg = 0;
	Double accumulated = 0;

	WellListPointers blankWells;

	for (WellMatrixList::size_type i = 0; i < wellMatrixListRef.size(); ++i)
	{
		WellListPointers bwl = wellMatrixListRef[i].filterWellsPointersByType(TWellType::wlBlank);

		if (bwl.empty())
			continue;

		std::copy(bwl.begin(), bwl.end(), std::back_inserter(blankWells));
	}

	if (blankWells.empty())
	{
		for (WellMatrixList::size_type i = 0; i < wellMatrixListRef.size(); ++i)
		{
			TWellMatrix& refMatrix = wellMatrixListRef[i];

			for (Integer row = 0; row < m_elisaDeviceParams->PlateRows; row++)       //exibe corretamente os dados linha/coluna após leitura
			{
				WellList& wlRef = refMatrix[row];

				for (WellList::iterator it = wlRef.begin(); it != wlRef.end(); it++)
				{
					if (it->Type == TWellType::wlEmpty)
						continue;

					it->RawBlankReducedValue = it->RawValue;
				}
			}
		}

		return;
	}

	for (WellListPointers::iterator it = blankWells.begin(); it != blankWells.end(); ++it)
		accumulated += (*it)->RawValue;

	blankAvg = accumulated / std::max((Double)blankWells.size(), 1.0);

	{
	for (WellMatrixList::size_type i = 0; i < wellMatrixListRef.size(); ++i)
	{
		TWellMatrix& refMatrix = wellMatrixListRef[i];

		for (Integer row = 0; row < m_elisaDeviceParams->PlateRows; row++)  //exibe corretamente os dados linha/coluna após leitura
		{
			for (WellList::iterator it = refMatrix[row].begin(); it != refMatrix[row].end(); it++)
			{
				if (it->Type == TWellType::wlEmpty)
					continue;

				if (it->Type == TWellType::wlBlank)
				{
					it->RawBlankReducedValue = blankAvg;
					continue;
				}

				it->RawBlankReducedValue = static_cast<Double>(it->RawValue - blankAvg);
			}
		}
	}
	}
}

void __fastcall TMainForm::DoProcessConcentrations()
{
	curveSerie->Clear();
	pointsSerie->Clear();

	switch (cbCurveTypes->ItemIndex)
	{
		case 0:
			MyDataModule->CalcLinearCurveFit(*mCalibrationCurve);
			break;

		case 1:
			MyDataModule->CalcLinearCurveFitCrossOrigin(*mCalibrationCurve);
			break;

		case 2:
			MyDataModule->CalcLinearLogCurveFit(*mCalibrationCurve);
			break;

		case 3:
			MyDataModule->CalcQuadraticCurveFit(*mCalibrationCurve);
			break;

		case 4:
			MyDataModule->CalcCubicSplineCurveFit(*mCalibrationCurve);
			break;

//		case 4:
//			MyDataModule->CalcLogitLogCurveFit(mEquationParameters);
//			break;
//
//		case 5:
//			MyDataModule->Calc4ParametersCurveFit(mEquationParameters);
//			break;
//
//		case 6:
//			MyDataModule->Calc5ParametersCurveFit(mEquationParameters);
//			break;
//
//		case 8:
//			MyDataModule->CalcPointToPointCurveFit(mEquationParameters);
//			break;

		default:
			throw Exception("Undefined curve type.");
			return;
	}

	cbChartScaleChange(NULL);
}


void __fastcall TMainForm::DoProcessCPnCNs()
{
	Single limit1Val = 0;
	Single limit2Val = 0;

	TValueKind       kind = (cbOrigin->ItemIndex == 0 ? TValueKind::Raw : TValueKind::Concentration);
	WellMatrixList&  wellMatrixListRef = *TWellMatrixSingleton::instance();

	this->NextDoProcessCPnCNs(kind, wellMatrixListRef);
	//this->PreviousDoProcessCPnCNs(kind, wellMatrixListRef);

	// Cálculo do limite 1
	loccusEval.SetExpression(edZone1Limit->Text.w_str());
	loccusEval.Evaluate();
	limit1Val = loccusEval.GetCurrValue();
	lbZone1Limit->Caption = Sysutils::Format(L"Limite Zona 1: %5.5f", ARRAYOFCONST((limit1Val)));

	// Cálculo do limite 2
	loccusEval.SetExpression(edZone2Limit->Text.w_str());
	loccusEval.Evaluate();
	limit2Val = loccusEval.GetCurrValue();
	lbZone2Limit->Caption = Sysutils::Format(L"Limite Zona 2: %5.5f", ARRAYOFCONST((limit2Val)));

	for (WellMatrixList::size_type i = 0; i < wellMatrixListRef.size(); ++i)
	{
		TWellMatrix& refMatrix = wellMatrixListRef[i];

		for (Integer row = 0; row < m_elisaDeviceParams->PlateRows; row++)          //exibe corretamente os dados linha/coluna após leitura
		{
			TWell& w = refMatrix[row].front();

			for (WellList::iterator it = refMatrix[row].begin(); it != refMatrix[row].end(); it++)
			{
				if (it->Type != TWellType::wlUnknown)
					continue;

				if (cbOrigin->ItemIndex == 0)
				{
					if (it->RawValue < limit1Val)
						it->Interpret = edZone1Interpret->Text;
					else
						if (it->RawValue >= limit1Val && it->RawValue < limit2Val)
							it->Interpret = String(edZone2Interpret->Text);
						else
							it->Interpret = String(edZone3Interpret->Text);
				}
				else
				{
					if (it->ConcentrationValue < limit1Val)
						it->Interpret = String(edZone1Interpret->Text);
					else
						if (it->ConcentrationValue >= limit1Val && w.ConcentrationValue < limit2Val)
							it->Interpret = String(edZone2Interpret->Text);
						else
							it->Interpret = String(edZone3Interpret->Text);
				}
			}
		}
	}
}


void __fastcall TMainForm::NextDoProcessCPnCNs(TValueKind kind, WellMatrixList& wellMatrixListRef)
{
	std::map<String, WellListPointers> Wells;
	std::map<String, double>           Summarizes;
	std::map<String, size_t>           Counts;

	try
	{
		Wells[L"CP"] = WellListPointers();
		Wells[L"CN"] = WellListPointers();

		for (WellMatrixList::size_type i = 0; i < wellMatrixListRef.size(); ++i)
		{
			for (int row = 0; row < wellMatrixListRef[i].Rows; row++)
			{
				for (WellList::iterator it = wellMatrixListRef[i][row].begin(); it != wellMatrixListRef[i][row].end(); it++)
				{
					String key = L"";

					switch (it->Type)
					{

						case TWellType::wlPositiveControl:
							key = L"CP";
							break;

						case TWellType::wlNegativeControl:
							key = L"CN";
							break;

						case TWellType::wlConcentrationStd:
							key = String("STD") + String(it->ID);
							if (Wells.find(key) == Wells.end())
							{
								Wells[key] = WellListPointers();
							}
							break;
					}

					if (key == "")
						continue;

					Wells[key].push_back(&(*it));
				}
			}
		}

		TSummarization summarization = TSummarization::Mean;
		//TSummarization summarization = TSummarization::Maximum;

		for(std::map<String, WellListPointers>::iterator item = Wells.begin(); item != Wells.end(); ++item)
		{
			if (item->second.size() == 0)
				throw std::runtime_error("Zero");

			Summarizes[item->first] = this->WellSummarize(item->second, summarization, kind);
		}

		// Start : Trecho para debug provisório das variáveis selecionadas
		String message = "";
		for(std::map<String, WellListPointers>::iterator item = Wells.begin(); item != Wells.end(); ++item)
		{
			double value = Summarizes[item->first];
			String name  = String(item->first.c_str());
			String item  = Sysutils::Format(L"%5s : %5.3f\n", ARRAYOFCONST((name, value)));

			message += item;
		}
		ShowMessage(message);
		// Finish

		for(std::map<String, WellListPointers>::iterator item = Wells.begin(); item != Wells.end(); ++item)
		{
			loccusEval.AddVariable(LME::Variable(item->first.c_str(), (Double)Summarizes[item->first]));
		}
	}
	catch (const std::exception& e)
	{
		ShowMessage(e.what());
	}
	catch(...)
	{
		ShowMessage("Erro inesperado");
	}
}


double __fastcall TMainForm::WellSummarize(WellListPointers Wells, TSummarization summarization, TValueKind kind)
{
	switch (summarization)
	{
		case TSummarization::Mean:
			{
				double Sum = 0;
				for (WellListPointers::iterator item = Wells.begin(); item != Wells.end(); ++item)
				{
					Sum += (kind == TValueKind::Raw) ? (*item)->RawValue : (*item)->ConcentrationValue;
				}
				return (Sum / Wells.size());
			}

		case TSummarization::Maximum:
			{
				double Maximum;
				double Current;
				bool   swap    = true;
				WellListPointers::iterator item = Wells.begin();
				while (true)
				{
					if (swap)
					{
						Maximum = (kind == TValueKind::Raw) ? (*item)->RawValue : (*item)->ConcentrationValue;
					}

					item++;
					if (item == Wells.end())
						break;

					swap = Maximum < ((kind == TValueKind::Raw) ? (*item)->RawValue : (*item)->ConcentrationValue);
				}
				return Maximum;
			}

		default:
			return 0;

	}
}


//calculo de CP e CN
void __fastcall TMainForm::PreviousDoProcessCPnCNs(TValueKind kind, WellMatrixList& wellMatrixListRef)
{
	using System::Sysutils::Format;

	Double accumulated = 0;

	WellListPointers cpWells;
	WellListPointers cnWells;
	WellListPointers stdWells;    // wlConcentrationStd

	// Preencher as listas cpWells, cnWells e stdWells
	for (WellMatrixList::size_type i = 0; i < wellMatrixListRef.size(); ++i)
	{
		WellListPointers cpwl = wellMatrixListRef[i].filterWellsPointersByType(TWellType::wlPositiveControl);
		if (!cpwl.empty())
			std::copy(cpwl.begin(), cpwl.end(), std::back_inserter(cpWells));

		WellListPointers cnwl = wellMatrixListRef[i].filterWellsPointersByType(TWellType::wlNegativeControl);
		if (!cnwl.empty())
			std::copy(cnwl.begin(), cnwl.end(), std::back_inserter(cnWells));

		WellListPointers stdwl = wellMatrixListRef[i].filterWellsPointersByType(TWellType::wlConcentrationStd);
		if (!stdwl.empty())
			std::copy(stdwl.begin(), stdwl.end(), std::back_inserter(stdWells));
	}

	Single limit1Val = 0;
	Single limit2Val = 0;
	Double cpAvg = 0, cnAvg = 0, stdAvg = 0;

	// Cálculo de CP
	if (!cpWells.empty())
	{
		accumulated = 0;
		for (WellListPointers::iterator it = cpWells.begin(); it != cpWells.end(); ++it)
		{
			if (cbOrigin->ItemIndex == 0)
				accumulated += (*it)->RawValue;
			else
				accumulated += (*it)->ConcentrationValue;
		}
		cpAvg = accumulated / (Double)cpWells.size();
	}

	// Cálculo de CN
	if (!cnWells.empty())
	{
		accumulated = 0;
		for (WellListPointers::iterator it = cnWells.begin(); it != cnWells.end(); ++it)
		{
			if (cbOrigin->ItemIndex == 0)
				accumulated += (*it)->RawValue;
			else
				accumulated += (*it)->ConcentrationValue;
		}
		cnAvg = accumulated / (Double)cnWells.size();
	}

	// Cálculo de STD (Padrões)
	if (!stdWells.empty())
	{
		accumulated = 0;
		for (WellListPointers::iterator it = stdWells.begin(); it != stdWells.end(); ++it)
		{
			switch (kind)
			{

				case TValueKind::Raw:
					accumulated += (*it)->RawValue;
					break;

				case TValueKind::Concentration:
					accumulated += (*it)->ConcentrationValue;
					break;

				default:
					accumulated = 0;
					break;
			}
		}
		stdAvg = accumulated / (Double)stdWells.size();
	}

	// Adicionar variáveis no loccusEval e calcular limites
	if (!cpWells.empty() && !cnWells.empty())
	{
		loccusEval.AddVariable(LME::Variable(TEXT("CP"), cpAvg));
		loccusEval.AddVariable(LME::Variable(TEXT("CN"), cnAvg));
		if (!stdWells.empty())
			loccusEval.AddVariable(LME::Variable(TEXT("STD"), stdAvg));

		// Cálculo do limite 1
		loccusEval.SetExpression(edZone1Limit->Text.w_str());
		loccusEval.Evaluate();
		limit1Val = loccusEval.GetCurrValue();
		lbZone1Limit->Caption = Format(_T("Limite Zona 1: %5.5f"), ARRAYOFCONST((limit1Val)));

		// Cálculo do limite 2
		loccusEval.SetExpression(edZone2Limit->Text.w_str());
		loccusEval.Evaluate();
		limit2Val = loccusEval.GetCurrValue();
		lbZone2Limit->Caption = Format(_T("Limite Zona 2: %5.5f"), ARRAYOFCONST((limit2Val)));
	}
}


//calculo de CP e CN
void __fastcall TMainForm::OldDoProcessCPnCNs()
{
	using System::Sysutils::Format;

	WellMatrixList& wellMatrixListRef = *TWellMatrixSingleton::instance();

	Double accumulated = 0;

	WellListPointers cpWells;
	WellListPointers cnWells;
	WellListPointers stdWells;    // wlConcentrationStd

	// Preencher as listas cpWells, cnWells e stdWells
	for (WellMatrixList::size_type i = 0; i < wellMatrixListRef.size(); ++i)
	{
		WellListPointers cpwl = wellMatrixListRef[i].filterWellsPointersByType(TWellType::wlPositiveControl);
		if (!cpwl.empty())
			std::copy(cpwl.begin(), cpwl.end(), std::back_inserter(cpWells));

		WellListPointers cnwl = wellMatrixListRef[i].filterWellsPointersByType(TWellType::wlNegativeControl);
		if (!cnwl.empty())
			std::copy(cnwl.begin(), cnwl.end(), std::back_inserter(cnWells));

		WellListPointers stdwl = wellMatrixListRef[i].filterWellsPointersByType(TWellType::wlConcentrationStd);
		if (!stdwl.empty())
			std::copy(stdwl.begin(), stdwl.end(), std::back_inserter(stdWells));
	}

	Single limit1Val = 0;
	Single limit2Val = 0;
	Double cpAvg = 0, cnAvg = 0, stdAvg = 0;

	// Cálculo de CP
	if (!cpWells.empty())
	{
		accumulated = 0;
		for (WellListPointers::iterator it = cpWells.begin(); it != cpWells.end(); ++it)
		{
			if (cbOrigin->ItemIndex == 0)
				accumulated += (*it)->RawValue;
			else
				accumulated += (*it)->ConcentrationValue;
		}
		cpAvg = accumulated / (Double)cpWells.size();
	}

	// Cálculo de CN
	if (!cnWells.empty())
	{
		accumulated = 0;
		for (WellListPointers::iterator it = cnWells.begin(); it != cnWells.end(); ++it)
		{
			if (cbOrigin->ItemIndex == 0)
				accumulated += (*it)->RawValue;
			else
				accumulated += (*it)->ConcentrationValue;
		}
		cnAvg = accumulated / (Double)cnWells.size();
	}

	// Cálculo de STD (Padrões)
	if (!stdWells.empty())
	{
		accumulated = 0;
		for (WellListPointers::iterator it = stdWells.begin(); it != stdWells.end(); ++it)
		{
			if (cbOrigin->ItemIndex == 0)
				accumulated += (*it)->RawValue;
			else
				accumulated += (*it)->ConcentrationValue;
		}
		stdAvg = accumulated / (Double)stdWells.size();
	}

	// Adicionar variáveis no loccusEval e calcular limites
	if (!cpWells.empty() && !cnWells.empty())
	{
		loccusEval.AddVariable(LME::Variable(TEXT("CP"), cpAvg));
		loccusEval.AddVariable(LME::Variable(TEXT("CN"), cnAvg));
		if (!stdWells.empty())
			loccusEval.AddVariable(LME::Variable(TEXT("STD"), stdAvg));

		// Cálculo do limite 1
		loccusEval.SetExpression(edZone1Limit->Text.w_str());
		loccusEval.Evaluate();
		limit1Val = loccusEval.GetCurrValue();
		lbZone1Limit->Caption = Format(_T("Limite Zona 1: %5.5f"), ARRAYOFCONST((limit1Val)));

		// Cálculo do limite 2
		loccusEval.SetExpression(edZone2Limit->Text.w_str());
		loccusEval.Evaluate();
		limit2Val = loccusEval.GetCurrValue();
		lbZone2Limit->Caption = Format(_T("Limite Zona 2: %5.5f"), ARRAYOFCONST((limit2Val)));
	}

	if (cnWells.empty() || cpWells.empty())
		return;


}


void __fastcall TMainForm::DoProcessQCs(WellList& ulp)
{
	WellMatrixList& wellMatrixListRef = *TWellMatrixSingleton::instance();

	for (WellMatrixList::size_type i = 0; i < wellMatrixListRef.size(); ++i)
	{
		WellList qcwl;

		wellMatrixListRef[i].filterWellsByType(TWellType::wlQualityControl, qcwl);

		if (qcwl.empty())
			continue;

		std::copy(qcwl.begin(), qcwl.end(), std::back_inserter(ulp));
	}
}

void __fastcall TMainForm::DoKineticRead(TWinControl *parent)
{
	using System::Sysutils::Format;

	TTreeNode *platesNode = getNode(TEXT("Placas"));
	TTreeNode *child = platesNode->getFirstChild();

	for (Integer i = tabAbsorbanceScrollBox->ControlCount-1; i >= 0; --i)
		tabAbsorbanceScrollBox->Controls[i]->Free();

	for (Integer i = tabConcentrationScrollBox->ControlCount-1; i >= 0; --i)
		tabConcentrationScrollBox->Controls[i]->Free();

	for (Integer i = tabQualitativeScrollBox->ControlCount-1; i >= 0; --i)
		tabQualitativeScrollBox->Controls[i]->Free();

	lvKineticTimes->ItemIndex = 0;

	KineticTimersList rl;

	for (Integer i = 0; i < lvKineticTimes->Items->Count; i++)
	{
		TTime tt;
		String sTime = lvKineticTimes->ItemPart(i, 1);

		StringToTime(sTime, tt);

		rl.push_back(tt);
	}

	std::unique_ptr<TKineticControler> kc(new TKineticControler(this, m_elisaDevice, rl));

	try
	{
	    WellMatrixList& wellMatrixListRef = *TWellMatrixSingleton::instance();

		for (currMatrix = 0; currMatrix < wellMatrixListRef.size(); currMatrix++)
		{
			kc->Execute(wellMatrixListRef[currMatrix]);

			if (currMatrix < wellMatrixListRef.size()-1)
			{
				m_elisaDevice->sendDoorCommand(True);

				if (m_elisaDevice->LastErrorCode != 0)
					return;

				if (!m_deviceSimulated)
					FrmWait->Close();

				TTreeNode *sibling = child->getNextSibling();

				String msg = Format("Coloque a placa \"%s\" e clique em \"Continuar\" para prosseguir.",
									ARRAYOFCONST((sibling->Text)));
				TModalResult r = MessageDlg(msg, mtConfirmation, TMsgDlgButtons() << mbOK << mbCancel, 0, mbOK);

				if (mrCancel == r)
				{
					m_elisaDevice->sendDoorCommand(False);

					do
					{
						m_elisaDevice->sendGetStatus();
					}
					while (m_elisaDevice->RunMode != RUN_MODE_IDLE);

					return;
				}

				if (!m_deviceSimulated)
					FrmWait->Show();

				m_elisaDevice->sendDoorCommand(False);

				do
				{
					m_elisaDevice->sendGetStatus();
				}
				while (m_elisaDevice->RunMode != RUN_MODE_IDLE);
			}
		}
	}
	catch (Exception& e)
	{
		Application->ShowException(&e);
		return;
	}
}

void __fastcall TMainForm::DoNormalRead(TWinControl *parent)
{
	using System::Sysutils::Format;

	for (Integer i = tabAbsorbanceScrollBox->ControlCount-1; i >= 0; --i)
		tabAbsorbanceScrollBox->Controls[i]->Free();

	for (Integer i = tabConcentrationScrollBox->ControlCount-1; i >= 0; --i)
		tabConcentrationScrollBox->Controls[i]->Free();

	for (Integer i = tabQualitativeScrollBox->ControlCount-1; i >= 0; --i)
		tabQualitativeScrollBox->Controls[i]->Free();

	TTreeNode *platesNode = getNode(_T("Placas"));
	TTreeNode *child = platesNode->getFirstChild();

	if (!m_deviceSimulated)
		FrmWait->Show();

	try
	{
	    WellMatrixList& wellMatrixListRef = *TWellMatrixSingleton::instance();

	 	for (currMatrix = 0; currMatrix < wellMatrixListRef.size(); currMatrix++)
		{
			if (chkbShake->Checked)
			{
				String sMM = meShakeDuration->Text.SubString(1, 2);
				String sSS = meShakeDuration->Text.SubString(4, 2);
				FrmWait->setTimePoint(sMM.ToIntDef(0) * 60 + sSS.ToIntDef(10));
			}

			m_elisaDevice->sendSetParams();
			m_elisaDevice->sendRunProgram();

			if (m_elisaDevice->LastErrorCode != 0)
				return;

			// Se configurou pra ler mais de uma placa, ele vai parar aqui, abrir a porta e esperar a proxima placa
			if (currMatrix < wellMatrixListRef.size()-1)
			{
				m_elisaDevice->sendDoorCommand(True);

				if (m_elisaDevice->LastErrorCode != 0)
					return;

				FrmWait->Close();

				TTreeNode *sibling = child->getNextSibling();

				String msg = Format("Coloque a placa \"%s\" e clique em \"Continuar\" para prosseguir.",
									ARRAYOFCONST((sibling->Text)));
				TModalResult r = MessageDlg(msg, mtConfirmation, TMsgDlgButtons() << mbOK << mbCancel, 0, mbOK);

				if (mrCancel == r)
				{
					m_elisaDevice->sendDoorCommand(False);

					do
					{
						m_elisaDevice->sendGetStatus();
					}
					while (m_elisaDevice->RunMode != RUN_MODE_IDLE);

					return;
				}

				FrmWait->Show();

				do
				{
					m_elisaDevice->sendGetStatus();
				}
				while (m_elisaDevice->RunMode != RUN_MODE_IDLE);

				child = sibling;
			}
		}
	}
	catch (Exception& e)
	{
		FrmWait->Close();
		Application->ShowException(&e);

		return;
	}
}

void __fastcall TMainForm::actProgramRunExecute(TObject *Sender)
{
	m_elisaDeviceParams->Filter1 = cbFilter1->ItemIndex;
	m_elisaDeviceParams->Filter2 = cbFilter2->ItemIndex;if ((m_elisaDeviceParams->ReadMode == TElisaReadMode::MultiWaveLength) &&
		(m_elisaDeviceParams->Filter2 == -1 || (m_elisaDeviceParams->Filter1 == m_elisaDeviceParams->Filter2)))
	{
		TaskMessageDlg(TEXT("Atenção"),

					   TEXT("O \"Filtro 2\" deve ser selecionado e deve ser diferente do \"Filtro 1\""),
					   mtWarning,
					   TMsgDlgButtons() << mbOK, 0);
		return;
	}

	if (chkbShake->Checked && meShakeDuration->Text.IsEmpty())
	{
		TaskMessageDlg(TEXT("Atenção"),
					   TEXT("O tempo de duração é obrigatório quando a \"Agitação\" está ativada."),
					   mtWarning,
					   TMsgDlgButtons() << mbOK, 0);
		return;
	}

	TTime t;
	if (chkbShake->Checked && !StringToTime(meShakeDuration->Text, t))
	{
		TaskMessageDlg(TEXT("Atenção"),
					   TEXT("Valor para o tempo de agitação inválido"),
					   mtWarning,
					   TMsgDlgButtons() << mbOK, 0);
		return;
	}

	TTime w;
//	if (!StringToTime(meWaitDuration->Text, w))
//	{
//		TaskMessageDlg(TEXT("Atenção"),
//					   TEXT("Valor para o tempo de espera inválido"),
//					   mtWarning,
//					   TMsgDlgButtons() << mbOK, 0);
//		return;
//	}

	m_elisaDeviceParams->Filter1 = cbFilter1->ItemIndex;
	m_elisaDeviceParams->Filter2 = cbFilter2->ItemIndex;
	m_elisaDeviceParams->CalcMethod = std::max<Integer>(0, cbCalcMethod->ItemIndex);

	if (ElisaDeviceTypeEnum::ElisaDeviceLMR96Flex == m_elisaDevice->Type)
	{
		m_elisaDeviceParams->Filter1 = spLambda1->Value;
		m_elisaDeviceParams->Filter2 = spLambda2->Value;
		m_elisaDeviceParams->CalcMethod = std::max<Integer>(0, cbCalcMethod2->ItemIndex);
	}

	m_elisaDeviceParams->Shake   = chkbShake->Checked;
	m_elisaDeviceParams->ShakeIntensity = static_cast<TElisaShakeIntensity>(chbShakeIntensity->ItemIndex) + 1;
	m_elisaDeviceParams->ShakeMode = static_cast<TElisaShakeMode>(chbShakeMode->ItemIndex);
	m_elisaDeviceParams->ShakeDuration = t;

	m_elisaDeviceParams->ReadSpeed = static_cast<TElisaReadSpeed>(chbReadSpeed->ItemIndex);
	m_elisaDeviceParams->WaitDuration = w;

	WellMatrixList& wellMatrixListRef = *TWellMatrixSingleton::instance();
	for (WellMatrixList::size_type i = 0; i < wellMatrixListRef.size(); i++)
	{
		TWellMatrix& wlp = wellMatrixListRef[i];

		for (Integer row = 0; row < m_elisaDeviceParams->PlateRows; row++)    //exibe corretamente os dados linha/coluna após leitura
		{
			TWell& w = wlp[row][0];

			for (WellList::iterator it = wlp[row].begin(); it != wlp[row].end(); it++)
			{
				if (it->Type != TWellType::wlConcentrationStd)
					it->StdValue = 0;

				it->RawValue = 0;
				it->RawValueFilter2 = 0;
				it->RawBlankReducedValue = 0;
				it->ConcentrationValue = 0;
			}
		}
	}

	WellList wlEmpty;
	wellMatrixListRef[0].filterWellsByType(TWellType::wlEmpty, wlEmpty);
	if (wlEmpty.size() == m_elisaDeviceParams->PlateRows * m_elisaDeviceParams->PlateCols)
	{
		TaskMessageDlg(TEXT("Atenção"),
					   TEXT("Placa vazia! Para realizar um experimento, "
							"é necessário designar os tipos de leituras na janela \"Placas\"."),
					   mtWarning,
					   TMsgDlgButtons() << mbOK, 0);

		return;
	}

	WellListPointers stdWells = wellMatrixListRef[0].filterWellsPointersByType(TWellType::wlConcentrationStd);
	if (!stdWells.empty() && !mCurveImported)
	{
		Single total = 0;

		for (WellListPointers::const_iterator cIt = stdWells.begin(); cIt != stdWells.end(); cIt++)
			total += (*cIt)->StdValue;

		if (!total)
		{
			TaskMessageDlg(TEXT("Atenção"),
						   TEXT("Foram designados padrões, porém nenhum valor foi adicionado.\n"
								"Por favor insira os valores antes de continuar."),
						   mtWarning,
						   TMsgDlgButtons() << mbOK, 0);

			return;
		}
	}
	else
	{
		if (!stdWells.empty())
		{
			TaskMessageDlg(TEXT("Atenção"),
						   TEXT("Não é permitido ler uma placa caso hajam \"Padrões\""
								" designados e uma curva importada de outro experimento.\n"
								"Para continuar, primeiro remova os padrões ou inicie um novo Protocolo."),
						   mtWarning,
						   TMsgDlgButtons() << mbOK, 0);

			return;
		}
	}

	try
	{
		if (rbKinetic->Checked)
		{
			if (lvKineticTimes->Items->Count < 1)
			{
				TaskMessageDlg(TEXT("Atenção"),
							   TEXT("É necessário ao menos um elemento inserido na lista de "
									"intervalos de tempo, quando a leitura cinética está selecionada."),
							   mtWarning,
							   TMsgDlgButtons() << mbOK, 0);

				return;
			}

			DoKineticRead(this);
		}
		else
		{
			if (!m_deviceSimulated)
				FrmWait->Show();

			DoNormalRead(this);

			if (!m_deviceSimulated)
				FrmWait->Close();
		}

		if (m_elisaDevice->LastErrorCode != 0)
			return;

		DoProcessResults();
	}
	catch (Exception& e)
	{
		Application->ShowException(&e);
	}
}


void __fastcall TMainForm::actLabelAssignment(TObject *Sender)
{
	FrmLabelAssignment = new TFrmLabelAssignment(this, *TWellMatrixSingleton::instance());
	FrmLabelAssignment->ShowModal();
	FrmLabelAssignment->Free();
}


void __fastcall TMainForm::DoProcessResults()
{
	using System::Sysutils::Format;

	WellMatrixList& wellMatrixListRef = *TWellMatrixSingleton::instance();

	UpdateUi(False);

	WellList unknownWells;
	for (WellMatrixList::size_type i = 0; i < wellMatrixListRef.size(); i++)
	{
		WellList unkl;
		wellMatrixListRef[i].filterWellsByType(TWellType::wlUnknown, unkl);

		if (unkl.empty())
			continue;

		WellList::size_type size = unknownWells.size() + unkl.size();

		std::copy(unkl.begin(), unkl.end(), std::back_inserter(unknownWells));
	}

	/**//*************************************
	 * Lógica para blank
	 *****************************************/
	DoProcessBlanks();
	CalculateForReplicas(TWellType::wlBlank);

	/**//*************************************
	 * Lógica para Padrões
	 *****************************************/
	WellListPointers conclp = wellMatrixListRef.front().filterWellsPointersByType(TWellType::wlConcentrationStd);
	if (!conclp.empty() || mCurveImported)
		DoProcessConcentrations();

	CalculateForReplicas(TWellType::wlUnknown);

	WellList bkpUnknows = unknownWells;
	std::sort(bkpUnknows.begin(), bkpUnknows.end());

	WellList::size_type unElements = bkpUnknows.size();
	WellList::iterator last = std::unique(bkpUnknows.begin(), bkpUnknows.end());

	unElements = std::distance(bkpUnknows.begin(), last);
	bkpUnknows.resize(unElements);

	for (WellMatrixList::size_type i = 0, plateIdx = 0, rowPos = 0; i < wellMatrixListRef.size(); ++i, plateIdx++)
	{
		WellList unkWells;
		wellMatrixListRef[i].filterWellsByType(TWellType::wlUnknown, unkWells);

		if (unkWells.empty())
			continue;

		for (WellList::iterator cit = unkWells.begin(); cit != unkWells.end(); cit++, rowPos++)
		{
			if (cit->PlateNumber > i)
			{
				unkWells.erase(unkWells.begin(), cit);
				break;
			}

			// Ajusta o resultado para as replicas
			WellListPointers wlr = wellMatrixListRef[i].getAllReplicas(*cit);

			Double avgConcReplica = 0, avgBlankReducedReplica = 0,
				   sumConcReplica = 0, sumBlankReducedReplica = 0;

			for (WellListPointers::iterator it = wlr.begin(); it != wlr.end(); it++)
			{
				sumConcReplica += (*it)->ConcentrationValue;
				sumBlankReducedReplica += (*it)->RawBlankReducedValue;
			}

			WellListPointers::size_type totalReplicas = std::max<WellListPointers::size_type>(wlr.size(), 1);

			avgConcReplica = sumConcReplica / totalReplicas;
			avgBlankReducedReplica = sumBlankReducedReplica / totalReplicas;

			for (WellListPointers::iterator it = wlr.begin(); it != wlr.end(); it++)
			{
				(*it)->ConcentrationValue = avgConcReplica;
				(*it)->RawBlankReducedValue = avgBlankReducedReplica;
			}
		}
	}

	/**//************************************************
	 * Lógica para Controle Positivo e Controle Negativo
	 ****************************************************/
	if (!unknownWells.empty())
		DoProcessCPnCNs();

	/**//*************************************
	 * Lógica para Quality Control
	 *****************************************/
	if (!unknownWells.empty())
		DoProcessQCs(unknownWells);

	CalculateForReplicas(TWellType::wlNegativeControl);
	CalculateForReplicas(TWellType::wlPositiveControl);
	CalculateForReplicas(TWellType::wlQualityControl);
	CalculateForReplicas(TWellType::wlConcentrationStd);

	Integer rowPos = 0, plateIdx = 0;

	std::sort(unknownWells.begin(), unknownWells.end());

	unElements = unknownWells.size();
	last = std::unique(unknownWells.begin(), unknownWells.end());

	unknownsGrid->DataRowCount = 0;
	unknownsGrid->DataRowCount = unElements;

	unknownsGrid->BeginUpdate();

	for (WellMatrixList::size_type i = 0, plateIdx = 0, rowPos = 0; i < wellMatrixListRef.size(); ++i, plateIdx++)
	{
		WellListPointers unkWells = wellMatrixListRef[i].filterWellsPointersByType(TWellType::wlUnknown);

		if (unkWells.empty())
			continue;

for (Integer col = 0; col < m_elisaDeviceParams->PlateCols; ++col)
{
    for (Integer row = 0; row < m_elisaDeviceParams->PlateRows; ++row)
	{
        for (WellListPointers::iterator cit = unkWells.begin(); cit != unkWells.end(); ++cit)
		{
            if ((*cit)->PlateNumber > i)
                break;

            // Verifica se o poço atual é o que estamos processando
            if ((*cit)->Row == row && (*cit)->Col == col)
			{
                String wellInfo;
                wellInfo.sprintf(TEXT("%c%2.2d"), row + 'A', col + 1);

                unknownsGrid->Cells[colUnknownPlateName->Position][rowPos] = getNode(plateIdx + 101)->Text;
                unknownsGrid->Cells[colUnknownCoord->Position][rowPos] = wellInfo;
                unknownsGrid->Cells[colUnknownWellID->Position][rowPos] = Format(TEXT("%2.2d"), ARRAYOFCONST(((*cit)->ID)));
                unknownsGrid->Cells[colUnknownPosProcessValue->Position][rowPos] = (*cit)->RawBlankReducedValue;
                unknownsGrid->Cells[colUnknownConcentrationValue->Position][rowPos] = (*cit)->ConcentrationValue;
                unknownsGrid->Cells[colUnknownStdDev->Position][rowPos] = (*cit)->StdDeviation;
                unknownsGrid->Cells[colUnknownCoefVar->Position][rowPos] = (*cit)->CoefVariation;
                unknownsGrid->Cells[colUnknownInterpretValue->Position][rowPos] = (*cit)->Interpret;

				rowPos++; // Incrementa a posição somente após adicionar o poço correspondente
            }
        }
    }
 }
}
	unknownsGrid->EndUpdate();

	/**//*************************************
	 * Normaliza as réplicas
	 *****************************************/
	rowPos = plateIdx = 0;

	ReadRawGrid->Enabled = False;
	// Popula grid com valores RAW (Aba de resultados RAW)
	ReadRawGrid->DataRowCount = 0;
	ReadRawGrid->DataRowCount = m_elisaDeviceParams->PlateRows * m_elisaDeviceParams->PlateCols * wellMatrixListRef.size();

	ReadRawGrid->BeginUpdate();
	for (Integer plateNumber = 0; plateNumber < wellMatrixListRef.size(); plateNumber++, plateIdx++)
	{
		for (Integer col = 0; col < m_elisaDeviceParams->PlateCols; col++)      //verificar se há problema no linha/coluna
		{
			for (Integer row = 0; row < m_elisaDeviceParams->PlateRows; row++, rowPos++)
			{
				TWell& w = (wellMatrixListRef[plateNumber])[row][col];

				String wellInfo;
				wellInfo.sprintf(TEXT("%c%2.2d"), w.Row+'A', w.Col+1);

				ReadRawGrid->Cells[colReadRawPlateName->Position][rowPos] = getNode(plateIdx+101)->Text;
				ReadRawGrid->Cells[colReadRawCoord->Position][rowPos] = wellInfo;
				ReadRawGrid->Cells[colReadWellID->Position][rowPos] = Format(TEXT("%2.2d"), ARRAYOFCONST((w.ID)));
				ReadRawGrid->Cells[colReadRawType->Position][rowPos]  = w.typeToString();
				ReadRawGrid->Cells[colReadRawValue->Position][rowPos] = w.RawValue;
				ReadRawGrid->Cells[colReadRawBlankReducedValue->Position][rowPos] = w.RawBlankReducedValue;
				ReadRawGrid->Cells[colPostprocessedValue->Position][rowPos] = (Double)w.ConcentrationValue;
				ReadRawGrid->Cells[colStdDeviation->Position][rowPos] = w.StdDeviation;
				ReadRawGrid->Cells[colCoefVariation->Position][rowPos] = w.CoefVariation;
				ReadRawGrid->Cells[colReadRawInterpretValue->Position][rowPos] = w.Interpret;

				if (w.Timestamp != TTime(0))
					ReadRawGrid->Cells[colReadRawTimestampValue->Position][rowPos] = FormatDateTime("hh:nn:ss", w.Timestamp);
			}
		}
	}
	ReadRawGrid->EndUpdate();
	ReadRawGrid->Enabled = True;

	TTreeNode *platesNode = getNode(_T("Placas"));
	TTreeNode *child = platesNode->getFirstChild();

	for (WellMatrixList::iterator mit = wellMatrixListRef.begin();
		 mit != wellMatrixListRef.end(); mit++, child = child->getNextSibling())
		 AddResultPlate(std::distance(wellMatrixListRef.begin(), mit), child->Text);

	UpdateUi(True);

	pageControl->ActivePage = tabResults;

	acRawResult->Enabled = True;
	acResultsRaw->Enabled = True;
	acResultUnknows->Enabled = True;
    OptExperimentSave->Enabled = True;
	OptExperimentExportCSV->Enabled = True;
	OptExportarValoresBrutos->Enabled = True;

    if (!mCurveImported)
        mCalibrationCurve->timestamp = Now();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbFilter2Change(TObject *Sender)
{
	if (cbFilter2->ItemIndex == cbFilter1->ItemIndex)
	{
		TaskMessageDlg(TEXT("Valor não permitido"),
						   TEXT("O Filtro 2 deve ser diferente do Filtro 1!"),
						   mtError,
						   TMsgDlgButtons() << mbCancel, 0);
		cbFilter2->ItemIndex = -1;
		return;
	}

	if (cbFilter2->ItemIndex > 0)
		m_elisaDeviceParams->Filter2 = cbFilter2->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbFilter1Change(TObject *Sender)
{
	m_elisaDeviceParams->Filter1 = cbFilter1->ItemIndex;

	cbFilter2->ItemIndex = -1;
}
//---------------------------------------------------------------------------
// Quando a leitura eh feita pelo equipamento
void __fastcall TMainForm::OnLMR96ReadDone(TObject *Sender, const RawDataMatrix& matrix, const RawDataMatrix& matrixFilter2)
{
	TWellMatrix& refMatrix = (*TWellMatrixSingleton::instance())[currMatrix];

	for (RawDataMatrix::size_type row = 0; row < m_elisaDeviceParams->PlateRows; row++)     //exibe corretamente os dados linha/coluna após leitura
	{
        WellList::iterator it = refMatrix[row].begin();

		for (RawDataMatrix::size_type col = 0; col < m_elisaDeviceParams->PlateCols; col++, it++)  {
			it->RawValue = matrix[row][col];
			if (m_elisaDeviceParams->Filter2 > 0)
				it->RawValueFilter2 = matrixFilter2[row][col];
		}
	}
}

void __fastcall TMainForm::acRawResultExecute(TObject *Sender)  //exportar resultados por placa /main menu
{
	FillResultsList();

	resultsCount = 0;
	frxUserDataSetResults->RangeEndCount = tabAbsorbanceScrollBox->ControlCount * tabResultPageControl->PageCount;
	frxReportRawResult->PrepareReport();
	frxReportRawResult->ShowPreparedReport();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::actOpenCloseDoorExecute(TObject *Sender)
{
	if (!m_deviceSimulated)
	{
		FrmWait->Show();

		m_elisaDevice->sendDoorCommand(!m_elisaDevice->DoorStatus);

		do
		{
			m_elisaDevice->sendGetStatus();
		}
		while (m_elisaDevice->RunMode != RUN_MODE_IDLE);

		FrmWait->Close();
	 }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tabStandardsBeforeShowPage(TObject *Sender)
{
	stdValuesGrid->Cells[0][0] = "Placa #";
	stdValuesGrid->ColWidths[0] = 100;
	stdValuesGrid->Cells[1][0] = "Padrão";
	stdValuesGrid->ColWidths[1] = 50;
	stdValuesGrid->Cells[2][0] = "Valor";
	stdValuesGrid->ColWidths[2] = 80;
	stdValuesGrid->Cells[3][0] = "Absorbância";
	stdValuesGrid->ColWidths[3] = 80;

	lmdstdValuesGrid->DataRowCount = 0;
	Integer row = 0;

	cbCurveTypes->Enabled = False;

	if (mCurveImported)
	{
		lmdstdValuesGrid->DataRowCount = mCalibrationCurve->stdValues.size();
		stdValuesGrid->RowCount = mCalibrationCurve->stdValues.size();

		std::vector< std::pair<Double, Double> >::const_iterator cit;

		Integer row = 0;

		for (cit = mCalibrationCurve->stdValues.begin(); cit != mCalibrationCurve->stdValues.end(); ++cit, row++)  //exibe corretamente os dados linha/coluna após leitura
		{
			lmdstdValuesGrid->Cells[colStdValue->Position][row]  = cit->second;
			lmdstdValuesGrid->Cells[colAbsorbance->Position][row] = cit->first;

			lmdstdValuesGrid->CurrentRow++;
		}

		return;
	}

	WellMatrixList& wellMatrixListRef = *TWellMatrixSingleton::instance();

	for (WellMatrixList::size_type matIndex = 0; matIndex < wellMatrixListRef.size(); matIndex++)
	{
		WellList wl;

		wellMatrixListRef[matIndex].filterWellsByType(TWellType::wlConcentrationStd, wl);

		if (wl.empty())
			continue;

		std::sort(wl.begin(), wl.end());
		WellList::iterator last = std::unique(wl.begin(), wl.end());

		wl.erase(last, wl.end());

		lmdstdValuesGrid->DataRowCount += wl.size();
		stdValuesGrid->RowCount += wl.size()-1;

		for (WellList::const_iterator cit = wl.begin(); cit != wl.end(); ++cit, row++)   //exibe corretamente os dados linha/coluna após leitura
		{
			stdValuesGrid->Cells[0][row+1] = getNode(matIndex+101)->Text;
			stdValuesGrid->Cells[1][row+1] = cit->ID;
			stdValuesGrid->Cells[2][row+1] = FloatToStrF((Double)cit->StdValue, ffFixed, 6, 3);
			stdValuesGrid->Cells[3][row+1] = FloatToStrF((Double)cit->RawBlankReducedValue, ffFixed, 6, 3);
		}

		cbCurveTypes->Enabled = True;
	}

	cbCurveTypes->ItemIndex = mCurveTypes;
	lmdstdValuesGrid->CurrentRow = 0;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::colStdValueParse(TObject *Grid, TLMDGridColumn *Column, TLMDString &TextValue, Variant &ResultValue,
		  bool &IsNull, bool &ParsedOk, PLMDString PErrMsg, bool CanRaiseError)
{
	if (mCurveImported)
		return;

	if (!ParsedOk)
		throw new Exception("Valor inserido inválido.");

	WellMatrixList& wellMatrixListRef = *TWellMatrixSingleton::instance();

	Integer cellId = (Integer)lmdstdValuesGrid->Cells[colReplicaNo->Position][lmdstdValuesGrid->CurrentRow];

	TWell w;

	w.PlateNumber = 0;
	w.ID = cellId;
	w.Type = TWellType::wlConcentrationStd;

	WellListPointers wl = wellMatrixListRef.front().getAllReplicas(w);

	if (!wl.empty())
	{
		for (WellListPointers::iterator it = wl.begin(); it < wl.end(); ++it)
			(*it)->StdValue = static_cast<Double>(ResultValue);
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
	if (INVALID_HANDLE_VALUE != singletonEventHandle)
	{
		ReleaseMutex(singletonEventHandle);
		singletonEventHandle = NULL;
	}

	UnregisterDeviceNotification(hDevNotify);

    if (!mResultsList.empty())
    {
        for (ResultsVector::size_type i = 0; i < mResultsList.size(); i++)
        {
            ResultPair pair = mResultsList[i];
            TPicture *pic = pair.second;

            pic->Free();
        }

        mResultsList.clear();
	}

	FrmWait->Free();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::treeviewAddPlateNode(TTreeNodes *Node)
{
	TTreeNode *node = getNode("Placas", Node->GetFirstNode());

	WellMatrixList& wellMatrixListRef = *TWellMatrixSingleton::instance();

    size_t matrixCount = wellMatrixListRef.size();

	TTreeNode *plateNode = Node->AddChildObject(node, String("Placa #") + matrixCount, NULL);
	plateNode->SelectedIndex = node->SelectedIndex + matrixCount;

	TTVChangedEvent ev = treeview->OnChange;
	treeview->OnChange = NULL;
	treeview->Selected = plateNode;
	treeview->OnChange = ev;

	treeview->Invalidate();
}

void __fastcall TMainForm::treeviewRemovePlateNode(TTreeNode *Node)
{
	TTreeNode *platesNode = getNode(TEXT("Placas"));

	TTVChangedEvent ev = treeview->OnChange;
	treeview->OnChange = NULL;
	Node->Delete();
	treeview->OnChange = ev;

	Integer i = 0;

	TTreeNode *node = platesNode->getFirstChild();
	while (node)
	{
		node->SelectedIndex = platesNode->SelectedIndex + (++i);
		node = node->getNextSibling();
	}
}

TTreeNode * __fastcall TMainForm::getNode(Integer index, TTreeNode *node) const
{
	if (!node)
		node = treeview->Items->GetFirstNode();

	while (node != NULL)
	{
		if (index == node->SelectedIndex)
			return node;

		if (node->HasChildren)
		{
			TTreeNode *child = getNode(index, node->getFirstChild());

            while (child != NULL)
            {
                if (child->SelectedIndex == index)
                    return child;

                child = child->getNextSibling();
            }
		}

		node = node->getNextSibling();
	}

	return NULL;
}

TTreeNode * __fastcall TMainForm::getNode(String name, TTreeNode *node) const
{
	if (!node)
		node = treeview->Items->GetFirstNode();

	while (node != NULL)
	{
		if (node->Text == name)
			return node;

		if (node->HasChildren)
		{
			TTreeNode *child = getNode(name, node->getFirstChild());

            while (child != NULL)
            {
                if (child->Text == name)
                    return child;

                child = child->getNextSibling();
            }
		}

		node = node->getNextSibling();
	}

	return NULL;
}

void __fastcall TMainForm::setNodeEnabled(TTreeNode *node, Boolean enabled)
{
	node->Enabled = enabled;

	if (node->HasChildren)
    {
		TTreeNode *child = node->getFirstChild();

		while (child)
		{
			child->Enabled = enabled;
			child = child->getNextSibling();
		}
	}
}

void __fastcall TMainForm::AddPlateMenuItemClick(TObject *Sender)
{
	TTreeNode *platesNode = getNode(_T("Placas"));

	WellMatrixList& wellMatrixListRef = *TWellMatrixSingleton::instance();

	wellMatrixListRef.push_back(TWellMatrix(m_elisaDeviceParams->PlateRows, m_elisaDeviceParams->PlateCols));
	currMatrix = wellMatrixListRef.size()-1;

	treeviewAddPlateNode(treeview->Items);

	TWellsEdit *pWellsEdit = new TWellsEdit(tabPlatesScrollBox, currMatrix);

	pWellsEdit->lbPlateCaption->Caption = platesNode->GetLastChild()->Text;

	pWellsEdit->Name = String("wellsEdit") + wellMatrixListRef.size();
	pWellsEdit->btnNegControl->Visible = (currMatrix < 1);
	pWellsEdit->btnPositiveControl->Visible = (currMatrix < 1);
	pWellsEdit->btnStd->Visible = (currMatrix < 1);
//	pWellsEdit->btnQC->Visible = (currMatrix < 1);

	const Integer controlHeight = (15 + pWellsEdit->Height);

	TControl *pc =  NULL;

	if (tabPlatesScrollBox->ControlCount)
		pc = tabPlatesScrollBox->Controls[tabPlatesScrollBox->ControlCount-1];

	Integer left = (tabPlatesScrollBox->Width / 2) - (pWellsEdit->Width / 2);

	pWellsEdit->Left = left;

	pWellsEdit->Top = 0;

	if (pc != NULL)
		pWellsEdit->Top = pc->Top + controlHeight;

	tabPlatesScrollBox->InsertControl(pWellsEdit);

	treeviewChange(this, treeview->Selected);

//    PostMessage(Handle, InternalMessages::WM_PLATE_ADDED, 0, reinterpret_cast<Longint>(pWellsEdit));
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RemovePlateMenuItemClick(TObject *Sender)
{
	TTreeNode *platesNode = getNode("Placas", treeview->TopItem);
	TTreeNode *node = treeview->Selected;

	WellMatrixList& wellMatrixListRef = *TWellMatrixSingleton::instance();

	Integer plateIndex = std::max<Integer>(node->SelectedIndex % platesNode->SelectedIndex, 1);

	TWellsEdit *pWe = dynamic_cast<TWellsEdit *>(tabPlatesScrollBox->Controls[plateIndex-1]);

	const Integer controlHeight = 15 + pWe->Height;

	if (tabPlatesScrollBox->ControlCount > 1)
	{
		for (Integer i = plateIndex-1; i < tabPlatesScrollBox->ControlCount; i++)
		{
			TControl *pControl = tabPlatesScrollBox->Controls[i];

			pControl->Top -= controlHeight;
		}
	}

	tabPlatesScrollBox->RemoveControl(pWe);

	pWe->Free();

	tabPlatesScrollBox->Invalidate();

	size_t wellMatrixLength = wellMatrixListRef.size();

	Integer index = std::max<Integer>(treeview->Selected->SelectedIndex - 101, 1);

	wellMatrixListRef.erase(wellMatrixListRef.begin() + index);

	wellMatrixLength = wellMatrixListRef.size();

	treeviewRemovePlateNode(treeview->Selected);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::treeviewMenuPopup(TObject *Sender)
{
	TTreeNode *platesNode = getNode("Placas", treeview->TopItem);
	Integer index = treeview->Selected->SelectedIndex - platesNode->SelectedIndex;

	AddPlateMenuItem->Enabled = False;
	RenamePlateMenuItem->Enabled = False;
	RemovePlateMenuItem->Enabled = False;

	if (index > 0 && index < 99)
	{
		AddPlateMenuItem->Enabled = True;
		RenamePlateMenuItem->Enabled = True;

		if (index > 1)
			RemovePlateMenuItem->Enabled = True;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RenamePlateMenuItemClick(TObject *Sender)
{
	TTreeNode *platesNode = getNode("Placas", treeview->TopItem);
	Integer index = treeview->Selected->SelectedIndex / platesNode->SelectedIndex;

	if (treeview->Selected->SelectedIndex > 0 && index < 100)
	{
		String newName;
		FrmRenamePlate = new TFrmRenamePlate(this, newName);
		Integer modalResult = FrmRenamePlate->ShowModal();
		FrmRenamePlate->Free();

		if (mrOk != modalResult)
			return;

		for (Integer i = 0; i < tabPlatesScrollBox->ControlCount; i++)
		{
			TWellsEdit *pWe = dynamic_cast<TWellsEdit *>(tabPlatesScrollBox->Controls[i]);

			if (pWe->lbPlateCaption->Caption == treeview->Selected->Text)
			{
				pWe->lbPlateCaption->Caption = newName;
				break;
			}
		}

		treeview->Selected->Text = newName;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbChartScaleChange(TObject *Sender)
{
//	stdCurveChart->LeftAxis->Automatic = True;
//	stdCurveChart->BottomAxis->Automatic = True;

	switch (cbChartScale->ItemIndex)
	{
		case 0:
            try
            {
                stdCurveChart->LeftAxis->Logarithmic = False;
                stdCurveChart->BottomAxis->Logarithmic = False;
            }
            catch (Exception& ex)
            {
                Application->ShowException(&ex);
            }
            break;

        case 1:
            try
            {
				if (0 > stdCurveChart->LeftAxis->Minimum || 0 > stdCurveChart->LeftAxis->Maximum)
				{
					String reason;

					reason.sprintf(TEXT("Para curva Logarítmica os eixos Y (%5.3f) e "
										"X (%5.3f) devem conter valore maiores de 0."),
										stdCurveChart->LeftAxis->Minimum, stdCurveChart->LeftAxis->Maximum);

					TaskMessageDlg(TEXT("Atenção"),
								   reason,
                                   mtWarning,
                                   TMsgDlgButtons() << mbOK, 0);

					cbChartScale->ItemIndex = 0;

					break;
				}

                stdCurveChart->LeftAxis->Logarithmic = False;
                stdCurveChart->BottomAxis->Logarithmic = True;
            }
            catch (Exception& ex)
            {
                Application->ShowException(&ex);
            }
            break;

        case 2:
            try
			{
				if (0 > stdCurveChart->LeftAxis->Minimum || 0 > stdCurveChart->LeftAxis->Maximum)
				{
					String reason;

					reason.sprintf(TEXT("Para curva Logarítmica os eixos Y (%5.3f) e "
										"X (%5.3f) devem conter valore maiores de 0."),
										stdCurveChart->LeftAxis->Minimum, stdCurveChart->LeftAxis->Maximum);

					TaskMessageDlg(TEXT("Atenção"),
								   reason,
                                   mtWarning,
                                   TMsgDlgButtons() << mbOK, 0);

					cbChartScale->ItemIndex = 0;

					break;
				}

                stdCurveChart->LeftAxis->Logarithmic = True;
                stdCurveChart->BottomAxis->Logarithmic = True;
            }
            catch (Exception& ex)
            {
                Application->ShowException(&ex);
            }
            break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tabQualityBeforeShowPage(TObject *Sender)
{
	QualitativeZoneChart->Axes->Left->Automatic = True;
	QualitativeZoneChart->Axes->Left->Minimum = 0;
	QualitativeZoneChart->Axes->Left->Maximum = 100;

	QualitativeZoneChart->Axes->Bottom->Automatic = True;
	QualitativeZoneChart->Axes->Bottom->Minimum = 0;
	QualitativeZoneChart->Axes->Bottom->Maximum = 100;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::rbFilterDoubleClick(TObject *Sender)
{
	m_elisaDeviceParams->ReadMode = TElisaReadMode::MultiWaveLength;
	lbFilter2->Enabled = True;
	cbFilter2->Enabled = True;
	cbFilter2->ItemIndex = -1;

	lbCalcMode->Enabled = True;
	cbCalcMethod->Enabled = True;
	cbCalcMethod->ItemIndex = 1;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::rbFilterSingleClick(TObject *Sender)
{
	m_elisaDeviceParams->ReadMode = TElisaReadMode::OneWaveLength;
	lbFilter2->Enabled = False;
	cbFilter2->Enabled = False;
	cbFilter2->ItemIndex = -1;

	lbCalcMode->Enabled = False;
	cbCalcMethod->Enabled = False;
	cbCalcMethod->ItemIndex = -1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbCalcMethodChange(TObject *Sender)
{
	m_elisaDeviceParams->CalcMethod = cbCalcMethod->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::rbKineticClick(TObject *Sender)
{
	m_elisaDeviceParams->ReadType = TElisaReadType::Kinetic;

	grpKineticParams->Visible = True;
	lbKineticType->Enabled = True;
	cbKineticType->Enabled = True;
	lbKineticRateType->Enabled = True;
	cbKineticRateType->Enabled = True;

	cbKineticTypeChange(Sender);

	lvKineticTimes->Enabled = True;
	btnAdd->Enabled = True;
	btnSub->Enabled = Boolean(lvKineticTimes->Items->Count > 0);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::rbEndPointClick(TObject *Sender)
{
	m_elisaDeviceParams->ReadType = TElisaReadType::Normal;

	grpKineticParams->Visible = False;
	lbKineticType->Enabled = False;
	cbKineticType->Enabled = False;
	lbKineticRateType->Enabled = False;
	cbKineticRateType->Enabled = False;
	lbKineticWindowType->Enabled = False;
	cbKineticWindowType->Enabled = False;
	lbKineticReactionType->Enabled = False;
	cbKineticReactionType->Enabled = False;
	lbKineticBaselineReadings->Enabled = False;
	spKineticBaselineReadings->Enabled = False;
	lbKineticReadingsFromType->Enabled = False;
	cbKineticReadingsFromType->Enabled = False;
	lbKineticChangeTimeType->Enabled = False;
	cbKineticChangeTimeType->Enabled = False;
	lbKineticChangeThreshold->Enabled = False;
	spKineticChangeThreshold->Enabled = False;
	lvKineticTimes->Enabled = False;
	//btnAdd->Enabled = False;
	//btnSub->Enabled = False;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnAddClick(TObject *Sender)
{
	using System::UnicodeString::Format;

	lvKineticTimes->Items->Add(Format("%2d;%s;---", ARRAYOFCONST((lvKineticTimes->Items->Count+1, TEXT("00:00:10")))));

	btnSub->Enabled = Boolean(lvKineticTimes->Items->Count > 0);

	lvKineticTimes->ItemIndex = lvKineticTimes->Items->Count-1;
	spHours->Enabled = True;
	spMinutes->Enabled = True;
	spSeconds->Enabled = True;

	spHours->Value = 0;
	spMinutes->Value = 0;
	spSeconds->Value = 10;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::btnSubClick(TObject *Sender)
{
	lvKineticTimes->Items->Delete(lvKineticTimes->ItemIndex);

	for (Integer i = 0; i < lvKineticTimes->Items->Count; i++)
		lvKineticTimes->SetItemPart(i, 0, IntToStr(i+1));

	lvKineticTimes->ItemIndex = lvKineticTimes->Items->Count-1;

	if (lvKineticTimes->Items->Count == 0)
    {
		spHours->Value = 0;
		spMinutes->Value = 0;
		spSeconds->Value = 10;

		btnSub->Enabled = False;
	}

	spHours->Enabled = Boolean(lvKineticTimes->Items->Count > 0);
	spMinutes->Enabled = Boolean(lvKineticTimes->Items->Count > 0);
	spSeconds->Enabled = Boolean(lvKineticTimes->Items->Count > 0);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (m_elisaDevice->isConnected &&
		m_elisaDevice->Status == ElisaDeviceCommandStatus::ElisaDeviceCommand_Idle &&
		m_elisaDevice->LastErrorCode == 0)
		m_elisaDevice->Disconnect();
	else
		m_elisaDevice->Terminate();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::lvKineticTimesSelect(TObject *Sender)
{
	String sTime = lvKineticTimes->ItemPart(lvKineticTimes->ItemIndex, 1);

	TTime tt;
	StringToTime(sTime, tt);

	uint16_t hh = 0, mm = 0, ss = 0, ms = 0;
	DecodeTime(tt, hh, mm, ss, ms);

	spHours->Value = hh;
	spMinutes->Value = mm;
	spSeconds->Value = ss;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::spHoursChange(TObject *Sender)
{
	using System::UnicodeString::Format;

	if (lvKineticTimes->Count < 1)
		return;

	String sTime = Format("%2.2d:%2.2d:%2.2d",
						  ARRAYOFCONST((spHours->Value, spMinutes->Value, spSeconds->Value)));

	lvKineticTimes->SetItemPart(lvKineticTimes->ItemIndex, 1, sTime);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbKineticTypeChange(TObject *Sender)
{
	Integer index = cbKineticType->ItemIndex;

	lbKineticRateType->Enabled = False;
	cbKineticRateType->Enabled = False;
	lbKineticWindowType->Enabled = False;
	cbKineticWindowType->Enabled = False;
	lbKineticReactionType->Enabled = False;
	cbKineticReactionType->Enabled = False;
	lbKineticBaselineReadings->Enabled = False;
	spKineticBaselineReadings->Enabled = False;
	lbKineticReadingsFromType->Enabled = False;
	cbKineticReadingsFromType->Enabled = False;
	lbKineticChangeTimeType->Enabled = False;
	cbKineticChangeTimeType->Enabled = False;
	lbKineticChangeThreshold->Enabled = False;
	spKineticChangeThreshold->Enabled = False;

	m_elisaDeviceParams->KineticParams.Type = static_cast<TElisaKineticType>(index);

	switch (index)
	{
		case 1:
		case 2:
			lbKineticReactionType->Enabled = True;
			cbKineticReactionType->Enabled = True;
			lbKineticWindowType->Enabled = True;
			cbKineticWindowType->Enabled = True;

		case 0:
			lbKineticRateType->Enabled = True;
			cbKineticRateType->Enabled = True;
			break;

		case 3:
			lbKineticReactionType->Enabled = True;
			cbKineticReactionType->Enabled = True;
			lbKineticWindowType->Enabled = True;
			cbKineticWindowType->Enabled = True;
			lbKineticBaselineReadings->Enabled = True;
			spKineticBaselineReadings->Enabled = True;
			lbKineticReadingsFromType->Enabled = True;
			cbKineticReadingsFromType->Enabled = True;
			lbKineticChangeTimeType->Enabled = True;
			cbKineticChangeTimeType->Enabled = True;
			lbKineticChangeThreshold->Enabled = True;
			spKineticChangeThreshold->Enabled = True;
			break;

		default:
			break;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbKineticRateTypeChange(TObject *Sender)
{
	m_elisaDeviceParams->KineticParams.RateType = static_cast<TElisaKineticRateType>(cbKineticRateType->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbKineticWindowTypeChange(TObject *Sender)
{
	m_elisaDeviceParams->KineticParams.WindowType = static_cast<TElisaKineticWindowType>(cbKineticWindowType->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbKineticReactionTypeChange(TObject *Sender)
{
	m_elisaDeviceParams->KineticParams.ReactionType = static_cast<TElisaKineticReactionType>(cbKineticReactionType->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbKineticReadingsFromTypeChange(TObject *Sender)
{
	m_elisaDeviceParams->KineticParams.ReadingsFromType = static_cast<TElisaKineticReadingsFromType>(cbKineticReadingsFromType->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbKineticChangeTimeTypeChange(TObject *Sender)
{
	m_elisaDeviceParams->KineticParams.ChangeTimeType = static_cast<TElisaKineticChangeTimeType>(cbKineticChangeTimeType->ItemIndex);
}
//---------------------------------------------------------------------------

AnsiString ExtractNumbers(const AnsiString &input) {
    AnsiString result;
    for (int i = 1; i <= input.Length(); i++) {
        if (input[i] >= '0' && input[i] <= '9') {
            result += input[i];
        }
    }
    return result;
}

void __fastcall TMainForm::acFiltersConfigExecute(TObject *Sender)
{
	if (ElisaDeviceTypeEnum::ElisaDeviceLMR96 != m_elisaDevice->Type
		&& ElisaDeviceTypeEnum::ElisaDeviceLMR96_2023 != m_elisaDevice->Type )
		return;

	FrmFiltersEdit = new TFrmFiltersEdit(this);

	TLMR96Device* lmr96Device;
	if (m_elisaDevice->Type == ElisaDeviceTypeEnum::ElisaDeviceLMR96)
		lmr96Device = (TLMR96Device*)m_elisaDevice;
	else if (ElisaDeviceTypeEnum::ElisaDeviceLMR96_2023 == m_elisaDevice->Type)
		lmr96Device = (TLMR96Device*)m_elisaDevice; // alterar a tipagem caso precise para a v2023

	FrmFiltersEdit->Filters = lmr96Device->Filters;

	TModalResult mr = FrmFiltersEdit->ShowModal();
	if (mrCancel == mr)
	{
		FrmFiltersEdit->Free();
		return;
	}
	FrmWait->Show();
	lmr96Device->Filters = FrmFiltersEdit->Filters;
	m_elisaDevice->sendSetFilterList();

	FrmFiltersEdit->Free();
	cbFilter1->Items->Clear();
	cbFilter2->Items->Clear();

	TStringList *buffer_to_ini = new TStringList();
	for (size_t i = 0; i < FILTER_MAX; i++)
	{
		AnsiString filterName = AnsiString(lmr96Device->Filters.filter[i]).UpperCase();
		if (filterName.IsEmpty() ||
			filterName == "OFF"  ||
			filterName == "NO")
			continue;
		cbFilter1->Items->Add(filterName.LowerCase());
		cbFilter2->Items->Add(filterName.LowerCase());
		buffer_to_ini->Add(ExtractNumbers(filterName));
	}
	lmr96Device->mpFilters->setFilters(buffer_to_ini);
	lmr96Device->mpFilters->Save();
	delete buffer_to_ini;

	cbFilter1->ItemIndex = 0;
	cbFilter2->ItemIndex = -1;
	FrmWait->Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tabAbsorbanceScrollBoxMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
	for (Integer i = 0; i < Mouse->WheelScrollLines; i++)
	{
		try
		{
			if (WheelDelta > 0)
				tabAbsorbanceScrollBox->Perform(WM_VSCROLL, SB_LINEUP, 0);
			else
				tabAbsorbanceScrollBox->Perform(WM_VSCROLL, SB_LINEDOWN, 0);
		}
		__finally
		{
			tabAbsorbanceScrollBox->Perform(WM_VSCROLL, SB_ENDSCROLL, 0);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tabConcentrationScrollBoxMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
	for (Integer i = 0; i < Mouse->WheelScrollLines; i++)
	{
		try
		{
			if (WheelDelta > 0)
				tabConcentrationScrollBox->Perform(WM_VSCROLL, SB_LINEUP, 0);
			else
				tabConcentrationScrollBox->Perform(WM_VSCROLL, SB_LINEDOWN, 0);
		}
		__finally
		{
			tabConcentrationScrollBox->Perform(WM_VSCROLL, SB_ENDSCROLL, 0);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tabQualitativeScrollBoxMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
	for (Integer i = 0; i < Mouse->WheelScrollLines; i++)
	{
		try
		{
			if (WheelDelta > 0)
				tabQualitativeScrollBox->Perform(WM_VSCROLL, SB_LINEUP, 0);
			else
				tabQualitativeScrollBox->Perform(WM_VSCROLL, SB_LINEDOWN, 0);
		}
		__finally
		{
			tabQualitativeScrollBox->Perform(WM_VSCROLL, SB_ENDSCROLL, 0);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
	TControl *WinControl = FindVCLWindow(MousePos);

	Handled = Boolean(WinControl != NULL);

	if (!Handled)
		return;

	TScrollBox *scrollBox = dynamic_cast<TScrollBox *>(WinControl);

	for (Integer i = 1; i < Mouse->WheelScrollLines; i++)
	{
		try
		{
			if (WheelDelta > 0)
				scrollBox->Perform(WM_VSCROLL, SB_LINEUP, 0);
			else
				scrollBox->Perform(WM_VSCROLL, SB_LINEDOWN, 0);
		}
		__finally
		{
			scrollBox->Perform(WM_VSCROLL, SB_ENDSCROLL, 0);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AddResultPlate(Integer plateNumber, const String& plateName)
{
	TWellsShowOptionFlags flags = TWellsShowOptionFlags() << TWellsShowOption::shoAbsorbance;

	std::unique_ptr<TWellResult> pwe(new TWellResult(tabResults, plateNumber, flags));
	pwe->Name = String("WellResultAbsorbance") + tabAbsorbanceScrollBox->ControlCount;
	pwe->lbPlateCaption->Caption = plateName;

	Integer top = 0;

	for (Integer i = 0; i < tabAbsorbanceScrollBox->ControlCount; i++)
		top += tabAbsorbanceScrollBox->Controls[i]->Height + 15;

	Integer left = (tabAbsorbanceScrollBox->Width / 2) - (pwe->Width / 2);

	pwe->Left = left;
	pwe->Top  = top;

	tabAbsorbanceScrollBox->InsertControl(pwe.release());

	flags = TWellsShowOptionFlags() << TWellsShowOption::shoConcentration;

	pwe.reset(new TWellResult(tabResults, plateNumber, flags));
	pwe->Name = String("WellResultConcentration") + tabConcentrationScrollBox->ControlCount;
	pwe->lbPlateCaption->Caption = plateName;

	top = 0;

	for (Integer i = 0; i < tabConcentrationScrollBox->ControlCount; i++)
		top += tabConcentrationScrollBox->Controls[i]->Height + 15;

	left = (tabConcentrationScrollBox->Width / 2) - (pwe->Width / 2);

	pwe->Left = left;
	pwe->Top  = top;

	tabConcentrationScrollBox->InsertControl(pwe.release());

	flags = TWellsShowOptionFlags() << TWellsShowOption::shoQualitative;

	pwe.reset(new TWellResult(tabResults, plateNumber, flags));
	pwe->Name = String("WellResultQualitative") + tabQualitativeScrollBox->ControlCount;
	pwe->lbPlateCaption->Caption = plateName;

	top = 0;

	for (Integer i = 0; i < tabQualitativeScrollBox->ControlCount; i++)
		top += tabQualitativeScrollBox->Controls[i]->Height + 15;

	left = (tabQualitativeScrollBox->Width / 2) - (pwe->Width / 2);

	pwe->Left = left;
	pwe->Top  = top;

	tabQualitativeScrollBox->InsertControl(pwe.release());
}

TPicture * __fastcall TMainForm::ResultPlateToImage(TWellResult *pWellResult)
{
	TBitmap *bitmap(new TBitmap);

    bitmap->PixelFormat = pf24bit;
	bitmap->Height = pWellResult->Height;
	bitmap->Width = pWellResult->Width;

	pWellResult->Update();
	pWellResult->PaintTo(bitmap->Canvas, 0, 0);

    TPicture *picture = new TPicture();
    picture->Assign(bitmap);

	return picture;
}

void __fastcall TMainForm::toolbarButtons0Click(TObject *Sender, int index)
{
	actConnectExecute(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::toolbarButtons1Click(TObject *Sender, int index)
{
	actDisconnectExecute(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::toolbarButtons2Click(TObject *Sender, int index)
{
	actProgramRunExecute(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::toolbarButtons3Click(TObject *Sender, int index)
{
	actOpenCloseDoorExecute(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::toolbarButtons4Click(TObject *Sender, int index)
{
	actLabelAssignment(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::FillUnitiesComboBox()
{
    DBModule->Lmr96Connection->Open();
    DBModule->UnidadesTable->Active = True;
    DBModule->UnitiesClientDataSet->Active = True;

    DBModule->UnitiesClientDataSet->First();

    cbUnity->Clear();

    while (!DBModule->UnitiesClientDataSet->Eof)
    {
        String unity = DBModule->UnitiesClientDataSet->FieldByName("UNIDADE")->AsString;

        cbUnity->Items->Add(unity);

        DBModule->UnitiesClientDataSet->Next();
    }

    cbUnity->ItemIndex = 2;
    cbUnityChange(NULL);

    DBModule->Lmr96Connection->CloseDataSets();
    DBModule->Lmr96Connection->Close();
}

void __fastcall TMainForm::FillFiltersComboBox()
{
	if (ElisaDeviceTypeEnum::ElisaDeviceLMR96 != m_elisaDevice->Type && ElisaDeviceTypeEnum::ElisaDeviceLMR96_2023 != m_elisaDevice->Type )
		return;

	cbFilter1->Items->Clear();
	cbFilter2->Items->Clear();

	for (size_t i = 0; i < FILTER_MAX; i++)
	{
		AnsiString filterName = AnsiString(m_elisaDevice->Filters.filter[i]).UpperCase();

		if (filterName.IsEmpty() ||
			filterName == "OFF"  ||
			filterName == "NO")
			continue;

		cbFilter1->Items->Add(filterName.LowerCase());
		cbFilter2->Items->Add(filterName.LowerCase());
	}

	cbFilter1->ItemIndex = 0;
	cbFilter2->ItemIndex = -1;
}

void __fastcall TMainForm::OptUserLoginClick(TObject *Sender)
{
	if (UserLogged())
	{
		MessageDlg("Existe um usuário ainda logado. Por favor, faça \"Logoff\" antes.",
				   mtInformation, TMsgDlgButtons() << mbOK, 0);

		return;
	}

	if (UserLogon() && !m_elisaDevice->isConnected)
		{
		actConnectExecute(Sender);
		UpdateUi(UserLogged());

        actConnect->Enabled = !m_elisaDevice->isConnected && UserLogged();
		actDisconnect->Enabled = m_elisaDevice->isConnected && UserLogged();
		actProgramRun->Enabled = m_elisaDevice->isConnected && UserLogged();
		actOpenCloseDoor->Enabled = m_elisaDevice->isConnected && UserLogged();
		}
	UpdateUi(UserLogged());
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OptUserLogoffClick(TObject *Sender)
{
	AskDialog->Title = TEXT("Desconexão do usuário ") + mpAppConfig->UserName;
	AskDialog->Content = TEXT("A desconexão de usuário implica na perda de dados.\n")
						 TEXT("Certifique-se de que o protocolo corrente ou o experimento foram salvos.\n")
						 TEXT("Deseja realmente prosseguir?");

	AskDialog->Execute();

	if (AskDialog->ResultButtonId != 200)
		return;

	InitAll();
	AddPlateMenuItemClick(Sender);

	CurrentProtocol = -1;
	mpAppConfig->UserID = -1;

	UpdateUi(False);

	OptUserLogoff->Enabled = False;
	OptUserLogin->Enabled = True;

    SMenuExperiment->Enabled = False;
    SMenuProtocol->Enabled = False;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TMainForm::InitSetup()
{
	rbEndPoint->Checked = True;
	rbKinetic->Checked = False;

	cbKineticType->ItemIndex = 0;
	cbKineticRateType->ItemIndex = 0;
	cbKineticWindowType->ItemIndex = 0;
	cbKineticReactionType->ItemIndex = 0;
	cbKineticReadingsFromType->ItemIndex = 0;
	spKineticChangeThreshold->Value = 1;
	cbKineticChangeTimeType->ItemIndex = 0;
	spKineticBaselineReadings->Value = 1;

	chkbShake->Checked = False;
	chbShakeIntensity->ItemIndex = 0;
	chbShakeMode->ItemIndex = 0;
	meShakeDuration->Text = "00:10";
	rbFilterSingle->Checked = True;
	cbFilter1->ItemIndex = 0;
	cbFilter2->ItemIndex = -1;
	cbCalcMethod->ItemIndex = -1;

	lvKineticTimes->Items->Clear();

    OptExperimentSave->Enabled = False;
}

void __fastcall TMainForm::InitCPCNParams()
{
	cbOrigin->ItemIndex = 0;
	edZone1Limit->Text = "";
	edZone1Interpret->Text = "";

	edZone2Limit->Text = "";
	edZone2Interpret->Text = "";

	edZone3Interpret->Text = "";
}

void __fastcall TMainForm::LoadSetupBranch(_di_IXMLNode ProtoNode)
{
	using System::Sysutils::Format;

    _di_IXMLNode ReadModeNode = ProtoNode->ChildNodes->FindNode("ReadMode");

    if (!ReadModeNode || !ReadModeNode->HasChildNodes)
    {
        TaskMessageDlg("Carregamento de Protocolo",
                       "Formato do arquivo inválido ou corrompido. Tag \"ReadMode\" não encontrada.",
                       mtError,
                       TMsgDlgButtons() << mbOK, 0);

        return;
    }

	_di_IXMLNode xmlNode = ReadModeNode->ChildNodes->FindNode("EndPoint");
    rbEndPoint->Checked = xmlNode->NodeValue;
    if (rbEndPoint->Checked)
        rbEndPointClick(this);

	xmlNode = ReadModeNode->ChildNodes->FindNode("Kinnectic");
    rbKinetic->Checked = xmlNode->NodeValue;

    if (rbKinetic->Checked)
    {
        rbKineticClick(this);

        xmlNode = ReadModeNode->ChildNodes->FindNode("Type");
        cbKineticType->ItemIndex = xmlNode->NodeValue;
        cbKineticTypeChange(this);

        xmlNode = ReadModeNode->ChildNodes->FindNode("TimeType");
        cbKineticRateType->ItemIndex = xmlNode->NodeValue;
        cbKineticRateTypeChange(this);

        xmlNode = ReadModeNode->ChildNodes->FindNode("Window");
        cbKineticWindowType->ItemIndex = xmlNode->NodeValue;
        cbKineticWindowTypeChange(this);

        xmlNode = ReadModeNode->ChildNodes->FindNode("Trend");
        cbKineticReactionType->ItemIndex = xmlNode->NodeValue;
        cbKineticReactionTypeChange(this);

        xmlNode = ReadModeNode->ChildNodes->FindNode("ReadOrder");
        cbKineticReadingsFromType->ItemIndex = xmlNode->NodeValue;
        cbKineticReadingsFromTypeChange(this);

        xmlNode = ReadModeNode->ChildNodes->FindNode("ChangeThreshold");
        spKineticChangeThreshold->Value = xmlNode->NodeValue;
        spKineticChangeThresholdChange(this);

        xmlNode = ReadModeNode->ChildNodes->FindNode("ChangeTimeType");
        cbKineticChangeTimeType->ItemIndex = xmlNode->NodeValue;
        cbKineticChangeTimeTypeChange(this);

        xmlNode = ReadModeNode->ChildNodes->FindNode("BaselineReadings");
        spKineticBaselineReadings->Value = xmlNode->NodeValue;
        spKineticBaselineReadingsChange(this);
    }

    _di_IXMLNode ShakeNode = ProtoNode->ChildNodes->FindNode("Shake");

    chkbShake->Checked = ShakeNode->HasChildNodes;
    chkbShakeClick(this);

    if (chkbShake->Checked)
    {
		xmlNode = ShakeNode->ChildNodes->FindNode("Type");
		chbShakeIntensity->ItemIndex = xmlNode->NodeValue;
		chbShakeIntensityChange(this);

		// TODO : testar isso aqui
	   //	xmlNode = ShakeNode->ChildNodes->FindNode("Mode");
	   //	chbShakeMode->ItemIndex = xmlNode->NodeValue;
	   //	chbShakeModeChange(this);

		xmlNode = ShakeNode->ChildNodes->FindNode("Duration");
		String timeValue = xmlNode->NodeValue;
		TTime t = StrToTime(timeValue);

		meShakeDuration->Text = FormatDateTime("nn:ss", t);
	}

_di_IXMLNode FiltersNode = ProtoNode->ChildNodes->FindNode("Filters");

if (FiltersNode && FiltersNode->HasChildNodes)
{
    // Configurar o estado dos botões primeiro
    xmlNode = FiltersNode->ChildNodes->FindNode("Single");
    rbFilterSingle->Checked = xmlNode && xmlNode->NodeValue == "true";

    xmlNode = FiltersNode->ChildNodes->FindNode("Double");
    rbFilterDouble->Checked = xmlNode && xmlNode->NodeValue == "true";

    // Chamar o evento correspondente para garantir a configuração correta
    if (rbFilterDouble->Checked)
    {
        rbFilterDoubleClick(this); // Garante que o modo Double é ativado corretamente
    }
    else if (rbFilterSingle->Checked)
    {
        rbFilterSingleClick(this); // Configura o modo Single, se necessário
    }

    // Preencher os comboboxes
    xmlNode = FiltersNode->ChildNodes->FindNode("Position1");
    if (xmlNode)
    {
        int pos1 = StrToInt(xmlNode->NodeValue);
        if (pos1 >= 0 && pos1 < cbFilter1->Items->Count)
        {
            cbFilter1->ItemIndex = pos1;
        }
    }

    xmlNode = FiltersNode->ChildNodes->FindNode("Position2");
    if (xmlNode)
    {
		int pos2 = StrToInt(xmlNode->NodeValue);
		if (pos2 >= 0 && pos2 < cbFilter2->Items->Count)
			{
				cbFilter2->ItemIndex = pos2;
			}
    }
}
	_di_IXMLNode WavesNode = ProtoNode->AddChild("WaveLenghts");
	if (WavesNode->HasChildNodes)
	{
		xmlNode = WavesNode->ChildNodes->FindNode("Single");
		rbSimpleLambda->Checked = xmlNode->NodeValue;

		if (rbSimpleLambda->Checked)
			rbSimpleLambdaClick(this);

		xmlNode = WavesNode->ChildNodes->FindNode("Double");
		rbDoubleLambda->Checked = xmlNode->NodeValue;

		if (rbDoubleLambda->Checked)
			rbDoubleLambdaClick(this);

		xmlNode = WavesNode->ChildNodes->FindNode("Lambda1");
		spLambda1->Value = xmlNode->NodeValue;

		xmlNode = WavesNode->ChildNodes->FindNode("Lambda2");
		spLambda2->Value = xmlNode->NodeValue;

		xmlNode = WavesNode->ChildNodes->FindNode("CalcMethod");
		cbCalcMethod2->ItemIndex = xmlNode->NodeValue;
	}

	_di_IXMLNode ShakeIntervalsNode = ProtoNode->ChildNodes->FindNode("ShakeIntervals");
	if (ShakeIntervalsNode->HasChildNodes)
	{
		lvKineticTimes->Items->Clear();

		xmlNode = ShakeIntervalsNode->ChildNodes->FindNode("CycleNum");

		while (xmlNode)
		{
            Integer cycleNum = xmlNode->NodeValue;

            xmlNode = xmlNode->NextSibling();

            String strTime = xmlNode->NodeValue;

	        lvKineticTimes->Items->Add(Format("%2d;%s;---", ARRAYOFCONST((cycleNum, strTime))));

            xmlNode = xmlNode->NextSibling();
        }
    }

    xmlNode = ProtoNode->ChildNodes->FindNode("CurveType");
    mCurveTypes = xmlNode->NodeValue;

    _di_IXMLNode QCParameters = ProtoNode->ChildNodes->FindNode("QCParameters");

    if (QCParameters->HasChildNodes)
    {
        xmlNode = QCParameters->ChildNodes->FindNode("Origin");
        cbOrigin->ItemIndex = xmlNode->NodeValue;

        _di_IXMLNode sessionNode = QCParameters->ChildNodes->FindNode("Session1");
        xmlNode = sessionNode->ChildNodes->FindNode("Interpret");
        edZone1Interpret->Text = xmlNode->NodeValue;

        xmlNode = sessionNode->ChildNodes->FindNode("Limit");
        edZone1Limit->Text = xmlNode->NodeValue;

        sessionNode = QCParameters->ChildNodes->FindNode("Session2");
        xmlNode = sessionNode->ChildNodes->FindNode("Interpret");
        edZone2Interpret->Text = xmlNode->NodeValue;

        xmlNode = sessionNode->ChildNodes->FindNode("Limit");
        edZone2Limit->Text = xmlNode->NodeValue;

        sessionNode = QCParameters->ChildNodes->FindNode("Session3");
        xmlNode = sessionNode->ChildNodes->FindNode("Interpret");
        edZone3Interpret->Text = xmlNode->NodeValue;
    }

    xmlNode = ProtoNode->ChildNodes->FindNode("Unity");

    if (xmlNode)
    {
        cbUnity->ItemIndex = xmlNode->NodeValue;
        cbUnityChange(NULL);
    }

    _di_IXMLNode platesNode = ProtoNode->ChildNodes->FindNode("Plates");

    if (platesNode->HasChildNodes)
		LoadPlatesBranch(platesNode);

	TTreeNode *node = treeview->Items->GetFirstNode();
	treeview->Selected = node;
}

void __fastcall TMainForm::CreateSetupBranch(_di_IXMLNode ProtoNode)
{
	using System::Sysutils::Format;

    _di_IXMLNode ReadModeNode = ProtoNode->AddChild("ReadMode");

    _di_IXMLNode xmlNode = ReadModeNode->AddChild("EndPoint");
    xmlNode->SetNodeValue(rbEndPoint->Checked? 1: 0);

    xmlNode = ReadModeNode->AddChild("Kinnectic");
    xmlNode->SetNodeValue(rbKinetic->Checked? 1: 0);

    xmlNode = ReadModeNode->AddChild("Type");
    xmlNode->SetNodeValue(cbKineticType->ItemIndex);

    xmlNode = ReadModeNode->AddChild("TimeType");
    xmlNode->SetNodeValue(cbKineticRateType->ItemIndex);

    xmlNode = ReadModeNode->AddChild("Window");
    xmlNode->SetNodeValue(cbKineticWindowType->ItemIndex);

    xmlNode = ReadModeNode->AddChild("Trend");
    xmlNode->SetNodeValue(cbKineticReactionType->ItemIndex);

    xmlNode = ReadModeNode->AddChild("ReadOrder");
    xmlNode->SetNodeValue(cbKineticReadingsFromType->ItemIndex);

	xmlNode = ReadModeNode->AddChild("ChangeThreshold");
	xmlNode->SetNodeValue(spKineticChangeThreshold->Value);

    xmlNode = ReadModeNode->AddChild("ChangeTimeType");
    xmlNode->SetNodeValue(cbKineticChangeTimeType->ItemIndex);

    xmlNode = ReadModeNode->AddChild("BaselineReadings");
    xmlNode->SetNodeValue(spKineticBaselineReadings->Value);

    if (chkbShake->Checked)
    {
        _di_IXMLNode ShakeNode = ProtoNode->AddChild("Shake");

		xmlNode = ShakeNode->AddChild("Type");
		xmlNode->SetNodeValue(chbShakeIntensity->ItemIndex);

		// TODO: testar isso aqui
		//xmlNode = ShakeNode->AddChild("Mode");
		//xmlNode->SetNodeValue(chbShakeMode->ItemIndex);

		xmlNode = ShakeNode->AddChild("Duration");
        xmlNode->SetNodeValue(FormatDateTime("hh:nn:ss", StrToTime("00:" + meShakeDuration->Text)));
    }
    else
        ProtoNode->AddChild("Shake");

	_di_IXMLNode FiltersNode = ProtoNode->AddChild("Filters");

    xmlNode = FiltersNode->AddChild("Single");
    xmlNode->SetNodeValue(rbFilterSingle->Checked);

    xmlNode = FiltersNode->AddChild("Double");
    xmlNode->SetNodeValue(rbFilterDouble->Checked);

    xmlNode = FiltersNode->AddChild("Position1");
	xmlNode->SetNodeValue(cbFilter1->ItemIndex);

	xmlNode = FiltersNode->AddChild("Position2");
	xmlNode->SetNodeValue(cbFilter2->ItemIndex);

	xmlNode = FiltersNode->AddChild("CalcMethod");
	xmlNode->SetNodeValue(cbCalcMethod->ItemIndex);

	xmlNode = FiltersNode->AddChild("FiltersValues");

	if (ElisaDeviceTypeEnum::ElisaDeviceLMR96 == m_elisaDevice->Type || ElisaDeviceTypeEnum::ElisaDeviceLMR96_2023 == m_elisaDevice->Type )
	{
		PLMR96Device lmr96Device = PLMR96Device(m_elisaDevice);

		for (size_t i = 0; i < FILTER_MAX; i++)
		{
			AnsiString filterName = AnsiString(lmr96Device->Filters.filter[i]).UpperCase();

			if (filterName.IsEmpty() ||
				filterName == "OFF"  ||
				filterName == "NO")
				continue;

			xmlNode->SetNodeValue(filterName.LowerCase());
		}
	}

    _di_IXMLNode WavesNode = ProtoNode->AddChild("WaveLenghts");

    xmlNode = WavesNode->AddChild("Single");
    xmlNode->SetNodeValue(rbSimpleLambda->Checked);

    xmlNode = WavesNode->AddChild("Double");
    xmlNode->SetNodeValue(rbDoubleLambda->Checked);

    xmlNode = WavesNode->AddChild("Lambda1");
    xmlNode->SetNodeValue(spLambda1->Value);

    xmlNode = WavesNode->AddChild("Lambda2");
    xmlNode->SetNodeValue(spLambda2->Value);

    xmlNode = WavesNode->AddChild("CalcMethod");
    xmlNode->SetNodeValue(cbCalcMethod2->ItemIndex);

    if (!lvKineticTimes->Count)
        ProtoNode->AddChild("ShakeIntervals");
    else
    {
        _di_IXMLNode ShakeIntervalsNode = ReadModeNode->AddChild("ShakeIntervals");

        for (Integer i = 0; i < lvKineticTimes->Count; i++)
        {
            Integer CycleNum = lvKineticTimes->ItemPart(i, 0).ToInt();
            TTime t = StrToTime(lvKineticTimes->ItemPart(i, 1));

            xmlNode = ShakeIntervalsNode->AddChild("CycleNum");
            xmlNode->SetNodeValue(CycleNum);

            xmlNode = ShakeIntervalsNode->AddChild("Interval");
            xmlNode->SetNodeValue(t.TimeString());
        }
    }

    _di_IXMLNode curveType = ProtoNode->AddChild("CurveType");
    curveType->SetNodeValue(cbCurveTypes->ItemIndex);

    _di_IXMLNode QCParameters = ProtoNode->AddChild("QCParameters");

	if (!edZone1Interpret->Text.IsEmpty() || !edZone2Interpret->Text.IsEmpty() ||
		!edZone3Interpret->Text.IsEmpty())
    {
        _di_IXMLNode xmlNode = QCParameters->AddChild("Origin");
        xmlNode->SetNodeValue(cbOrigin->ItemIndex);

        _di_IXMLNode sessionNode = QCParameters->AddChild("Session1");
        xmlNode = sessionNode->AddChild("Interpret");
		xmlNode->SetNodeValue(edZone1Interpret->Text);

        xmlNode = sessionNode->AddChild("Limit");
        xmlNode->SetNodeValue(edZone1Limit->Text);

        sessionNode = QCParameters->AddChild("Session2");
        xmlNode = sessionNode->AddChild("Interpret");
		xmlNode->SetNodeValue(edZone2Interpret->Text);

        xmlNode = sessionNode->AddChild("Limit");
        xmlNode->SetNodeValue(edZone2Limit->Text);

        sessionNode = QCParameters->AddChild("Session3");
        xmlNode = sessionNode->AddChild("Interpret");
		xmlNode->SetNodeValue(edZone3Interpret->Text);
    }

    xmlNode = ProtoNode->AddChild("Unity");
    xmlNode->SetNodeValue(cbUnity->ItemIndex);

	CreatePlatesBranch(ProtoNode);
}

void __fastcall TMainForm::LoadPlatesBranch(_di_IXMLNode PlatesNode)
{
	using System::Sysutils::Format;

	_di_IXMLNode plateNode = PlatesNode->ChildNodes->First();

	Integer PlateNum = 0;

	_di_IXMLNode xmlNode = plateNode->ChildNodes->FindNode("Height");
	m_elisaDeviceParams->PlateRows = xmlNode->NodeValue;

	xmlNode = plateNode->ChildNodes->FindNode("Width");
	m_elisaDeviceParams->PlateCols = xmlNode->NodeValue;

	WellMatrixList::size_type mIndex = 0;

	TTreeNode *treePlatesNode = NULL;

	while (plateNode)
	{
		xmlNode = plateNode->ChildNodes->FindNode("Height");
		m_elisaDeviceParams->PlateRows = xmlNode->NodeValue;

		xmlNode = plateNode->ChildNodes->FindNode("Width");
		m_elisaDeviceParams->PlateCols = xmlNode->NodeValue;

		AddPlateMenuItemClick(this);

	    WellMatrixList& wellMatrixListRef = *TWellMatrixSingleton::instance();

		TWellMatrix& refWellMatrix = wellMatrixListRef[mIndex++];

		String PlateName = plateNode->GetAttribute("Name");

		if (treePlatesNode == NULL)
			treePlatesNode = getNode("Placas")->getFirstChild();
		else
			treePlatesNode = treePlatesNode->getNextSibling();

		if (treePlatesNode->Text != PlateName)
			treePlatesNode->Text = PlateName;

		_di_IXMLNode layoutNode = plateNode->ChildNodes->FindNode("Layout");

		_di_IXMLNode wellNode = layoutNode->ChildNodes->FindNode("Well");

		for (Integer row = 0; row < m_elisaDeviceParams->PlateRows;  row++)      //iteração para preencher std values do experimento
		{
			WellList& wl = refWellMatrix[row];

			for (WellList::iterator it = wl.begin(); it != wl.end(); it++)
			{
				it->ID = wellNode->GetAttribute("ID");
				it->Row = wellNode->ChildValues["Row"] - 1;
				it->Col = wellNode->ChildValues["Col"] - 1;

				Integer wellType = wellNode->ChildValues["Type"];
				it->Type = static_cast<TWellType>(wellType);

                if (TWellType::wlConcentrationStd ==it->Type)
                    it->StdValue = wellNode->ChildValues["StdValue"];

				wellNode = wellNode->NextSibling();
			}
		}

		plateNode = plateNode->NextSibling();
	}
}

void __fastcall TMainForm::CreatePlatesBranch(_di_IXMLNode PlatesNode)
{
	WellMatrixList wellMatrixListRef = *TWellMatrixSingleton::instance();

	_di_IXMLNode xmlPlates = PlatesNode->AddChild("Plates");

	TTreeNode *platesNode = getNode("Placas")->getFirstChild();

	Integer PlateNum = 0;


	WellMatrixList::size_type matrixIndex = 0;

	while (platesNode)
	{
		_di_IXMLNode plate = xmlPlates->AddChild("Plate");
		plate->SetAttribute("Name", platesNode->Text);

		_di_IXMLNode xmlNode = plate->AddChild("Height");
		xmlNode->SetNodeValue(m_elisaDeviceParams->PlateRows);

		xmlNode = plate->AddChild("Width");
		xmlNode->SetNodeValue(m_elisaDeviceParams->PlateCols);

		_di_IXMLNode xmlLayout = plate->AddChild("Layout");

		TWellMatrix& refMatrix = wellMatrixListRef[matrixIndex++];

		for (Integer Row = 0; Row < m_elisaDeviceParams->PlateRows;  Row++)
		{
			for (Integer Col = 0; Col < m_elisaDeviceParams->PlateCols; Col++)
			{

				TWell& w = refMatrix[Row][Col];

				_di_IXMLNode xmlWell = xmlLayout->AddChild("Well");
				xmlWell->SetAttribute("ID", w.ID);

				_di_IXMLNode node = xmlWell->AddChild("Row");
				node->SetNodeValue(w.Row + 1);

				node = xmlWell->AddChild("Col");
				node->SetNodeValue(w.Col + 1);

				node = xmlWell->AddChild("Type");
				node->SetNodeValue(static_cast<Integer>(w.Type));

				node = xmlWell->AddChild("StdValue");
				node->SetNodeValue(w.StdValue);
			}
		}

		platesNode = platesNode->getNextSibling();
	}
}

//---------------------------------------------------------------------------
// Executado somente uma vez depois do FormShow
void __fastcall TMainForm::OneShotTimerTimer(TObject *Sender)
{
	OneShotTimer->Enabled = False;


	StlStringList commNames = m_elisaDevice->GetPortNames();

	if (commNames.empty())
	{
		MessageDlg(_T("µPlate - Nenhum equipamento compatível encontrado."),
				   mtWarning, TMsgDlgButtons() << mbOK, 0);

		toolbar->Buttons->Items[0]->Enabled = False;
		return;
	}

	commName = commNames[0];

	actConnectExecute(Sender);       // comando pra conectar ao equipamento

	UserLogon();

	UpdateUi(UserLogged());
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CreateResultsBranch(_di_IXMLNode ResultsNode)
{
	WellMatrixList wellMatrixListRef = *TWellMatrixSingleton::instance();

	_di_IXMLNode PlatesNode = ResultsNode->AddChild("Plates");

	for (WellMatrixList::size_type i = 0, PlateNum = 1; i < wellMatrixListRef.size(); i++, PlateNum++)
	{
		_di_IXMLNode plate = PlatesNode->AddChild("Plate");
		plate->SetAttribute("Number", PlateNum);

		TWellMatrix& refMatrix = wellMatrixListRef[i];

		for (Integer Row = 0; Row < m_elisaDeviceParams->PlateRows; Row++)
		{
			for (Integer Col = 0; Col < m_elisaDeviceParams->PlateCols; Col++)
			{

                TWell& w = refMatrix[Row][Col];

                _di_IXMLNode xmlWell = plate->AddChild("Well");
                xmlWell->SetAttribute("ID", w.ID);

                _di_IXMLNode node = xmlWell->AddChild("Row");
                node->SetNodeValue(w.Row+1);

                node = xmlWell->AddChild("Col");
				node->SetNodeValue(w.Col+1);

				node = xmlWell->AddChild("Type");
				node->SetNodeValue(static_cast<Integer>(w.Type));

				node = xmlWell->AddChild("RawValue");
				node->SetNodeValue(w.RawValue);
            }
        }
    }
}

void __fastcall TMainForm::LoadResultsBranch(_di_IXMLNode ResultsNode)
{
    WellMatrixList& wellMatrixListRef = *TWellMatrixSingleton::instance();

    _di_IXMLNode PlatesNode = ResultsNode->ChildNodes->FindNode("Plates");
    _di_IXMLNode PlateNode = PlatesNode->ChildNodes->First();

	if (!PlateNode)
    {
		TaskMessageDlg(TEXT("Carregar experimento"),
					   TEXT("Erro durante o carregamento dos resultados, arquivo incompleto ou corrompido."),
                       mtError,
					   TMsgDlgButtons() << mbOK, 0);
		return;
    }

	// Configurações de formato para garantir o ponto como separador decimal
    TFormatSettings fs;
    GetLocaleFormatSettings(LOCALE_USER_DEFAULT, fs);
    fs.DecimalSeparator = '.';
	fs.ThousandSeparator = '\0'; // Desabilita separador de milhar

    do
    {
        Integer PlateNum = PlateNode->GetAttribute("Number");

        TWellMatrix& refMatrix = wellMatrixListRef[PlateNum - 1];
        _di_IXMLNode wellNode = PlateNode->ChildNodes->First();

		for (Integer row = 0; row < m_elisaDeviceParams->PlateRows; row++)
		{
            for (WellList::iterator it = refMatrix[row].begin(); it != refMatrix[row].end(); it++)
            {
                _di_IXMLNode rawValueNode = wellNode->ChildNodes->FindNode("RawValue");
				if (rawValueNode)
                {
						String rawValueStr = rawValueNode->NodeValue;

// Normaliza o separador decimal conforme a configuração do software
if (fs.DecimalSeparator == ',')
{
    rawValueStr = StringReplace(rawValueStr, ".", ",", TReplaceFlags() << rfReplaceAll);
}
else
{
    rawValueStr = StringReplace(rawValueStr, ",", ".", TReplaceFlags() << rfReplaceAll);
}

try
{
	it->RawValue = StrToFloat(rawValueStr, fs);
					}
					catch (const EConvertError& e)
					{
						ShowMessage("Erro ao converter RawValue: " + rawValueNode->NodeValue);
						it->RawValue = 0.0; // Define um valor padrão em caso de erro
                    }
				}

				wellNode = wellNode->NextSibling();
            }
        }

		PlateNode = PlateNode->NextSibling();
	} while (PlateNode);
}


void __fastcall TMainForm::acConfPrefsExecute(TObject *Sender)
{
	FrmAppConfig = new TFrmAppConfig(this);
	FrmAppConfig->ShowModal();
    FrmAppConfig->Free();
	FrmAppConfig = NULL;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::cbUnityChange(TObject *Sender)
{
    mpAppConfig->ProtocolUnity = cbUnity->Items->Strings[cbUnity->ItemIndex];
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::frxReportRawResultBeforePrint(TfrxReportComponent *Sender)
{
	TfrxMemoView *frxMemo = dynamic_cast<TfrxMemoView *>(frxReportRawResult->FindObject("ResultTypeTitle"));

	if (!frxMemo)
    {
        TaskMessageDlg("Invalid Reference",
					   "Invalid reference to report object \"ResultTypeTitle\"",
                       mtError,
                       TMsgDlgButtons() << mbOK, 0);

        return;
    }

	ResultPair pair = mResultsList[frxUserDataSetResults->RecNo];

    frxMemo->Text = pair.first;

	TfrxPictureView *frxPic = dynamic_cast<TfrxPictureView *>(frxReportRawResult->FindObject("ResultPicture"));

    if (!frxPic)
    {
        TaskMessageDlg("Invalid Reference",
					   "Invalid reference to report object \"ResultPicture\"",
                       mtError,
                       TMsgDlgButtons() << mbOK, 0);

        return;
    }

    frxPic->Picture->Assign(pair.second);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::frxUserDataSetResultsCheckEOF(TObject *Sender, bool &Eof)
{
	if (frxUserDataSetResults->RecNo >= frxUserDataSetResults->RangeEndCount)
		Eof = True;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FillResultsList()
{
	if (!mResultsList.empty())
    {
        for (ResultsVector::size_type i = 0; i < mResultsList.size(); i++)
        {
            ResultPair pair = mResultsList[i];
            TPicture *pic = pair.second;

            pic->Free();
        }

        mResultsList.clear();
    }

    for (Integer i = 0; i < tabAbsorbanceScrollBox->ControlCount; i++)
    {
        TPicture *resultImg = ResultPlateToImage(dynamic_cast<TWellResult *>(tabAbsorbanceScrollBox->Controls[i]));
        ResultPair pair = std::make_pair<String, TPicture *>(TEXT("Absorbância"), resultImg);

        mResultsList.push_back(pair);
    }

    for (Integer i = 0; i < tabConcentrationScrollBox->ControlCount; i++)
    {
        TPicture *resultImg = ResultPlateToImage(dynamic_cast<TWellResult *>(tabConcentrationScrollBox->Controls[i]));
        ResultPair pair = std::make_pair<String, TPicture *>(TEXT("Concentração"), resultImg);

        mResultsList.push_back(pair);
    }

    for (Integer i = 0; i < tabQualitativeScrollBox->ControlCount; i++)
    {
		TPicture *resultImg = ResultPlateToImage(dynamic_cast<TWellResult *>(tabQualitativeScrollBox->Controls[i]));
        ResultPair pair = std::make_pair<String, TPicture *>(TEXT("Qualitativo"), resultImg);

        mResultsList.push_back(pair);
    }
}

void __fastcall TMainForm::frxUserDataSetResultsGetValue(const UnicodeString VarName, Variant &Value)
{
	ResultPair pair = mResultsList[frxUserDataSetResults->RecNo];

	if (VarName == "ResultType")
    {
        Value = pair.first;

		TfrxPictureView *frxPic = dynamic_cast<TfrxPictureView *>(frxReportRawResult->FindObject("ResultPicture"));

        if (!frxPic)
        {
            TaskMessageDlg("Invalid Reference",
						   "Invalid reference to report object \"ResultPicture\"",
                           mtError,
                           TMsgDlgButtons() << mbOK, 0);

            return;
        }

        frxPic->Picture->Assign(pair.second);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::spLambda1Change(TObject *Sender)
{
	using System::Sysutils::Format;
    StlString valueString = loccus::ToString(spLambda1->Value);

	if ((spLambda1->Value > spLambda1->MaxValue ||
    	 spLambda1->Value < spLambda1->MinValue) &&
         static_cast<Integer>(valueString.length()) >= spLambda1->MaxLength)
    {
        String msg = Format("Valor do comprimento de onda deve estar entre %d e %d",
        					ARRAYOFCONST((spLambda1->MinValue, spLambda1->MaxValue)));
        MessageDlg(msg, mtInformation, TMsgDlgButtons() << mbOK, 0);
        spLambda1->SetFocus();
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::spLambda2Change(TObject *Sender)
{
	using System::Sysutils::Format;
    StlString valueString = loccus::ToString(spLambda2->Value);

	if ((spLambda2->Value > spLambda2->MaxValue ||
    	 spLambda2->Value < spLambda2->MinValue) &&
         static_cast<Integer>(valueString.length()) >= spLambda2->MaxLength)
    {
        String msg = Format("Valor do comprimento de onda deve estar entre %d e %d",
        					ARRAYOFCONST((spLambda2->MinValue, spLambda2->MaxValue)));
        MessageDlg(msg, mtInformation, TMsgDlgButtons() << mbOK, 0);
        spLambda2->SetFocus();
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::rbSimpleLambdaClick(TObject *Sender)
{
    spLambda2->Enabled = False;
    cbCalcMethod2->Enabled = False;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::rbDoubleLambdaClick(TObject *Sender)
{
    spLambda2->Enabled = True;
	cbCalcMethod2->Enabled = True;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::spKineticChangeThresholdChange(TObject *Sender)
{
	m_elisaDeviceParams->KineticParams.ChangeThreshold = spKineticChangeThreshold->Value;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::spKineticBaselineReadingsChange(TObject *Sender)
{
	m_elisaDeviceParams->KineticParams.BaselineReadings = spKineticBaselineReadings->Value;
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::tabAbsorbanceScrollBoxResize(TObject *Sender)
{
	for (Integer i = 0; i < tabAbsorbanceScrollBox->ControlCount; i++)
	{
		TControl *pc =  tabAbsorbanceScrollBox->Controls[i];

		if (!pc)
			continue;


		Integer left = (tabAbsorbanceScrollBox->Width / 2) - (pc->Width / 2);
		pc->Left = left;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tabConcentrationScrollBoxResize(TObject *Sender)
{
	for (Integer i = 0; i < tabConcentrationScrollBox->ControlCount; i++)
	{
		TControl *pc =  tabConcentrationScrollBox->Controls[i];

		if (!pc)
			continue;


		Integer left = (tabConcentrationScrollBox->Width / 2) - (pc->Width / 2);
		pc->Left = left;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tabQualitativeScrollBoxResize(TObject *Sender)
{
	for (Integer i = 0; i < tabQualitativeScrollBox->ControlCount; i++)
	{
		TControl *pc =  tabQualitativeScrollBox->Controls[i];

		if (!pc)
			continue;


		Integer left = (tabQualitativeScrollBox->Width / 2) - (pc->Width / 2);
		pc->Left = left;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tabPlatesScrollBoxResize(TObject *Sender)
{
	for (Integer i = 0; i < tabPlatesScrollBox->ControlCount; i++)
	{
		TControl *pc =  tabPlatesScrollBox->Controls[i];

		if (!pc)
			continue;

		Integer left = (tabPlatesScrollBox->Width / 2) - (pc->Width / 2);
		pc->Left = left;
	}
}
//---------------------------------------------------------------------------

Boolean __fastcall TMainForm::AlreadyRunning()
{
	Boolean alreadyRunning = False;

	singletonEventHandle = OpenMutex(MUTEX_ALL_ACCESS, 0, APPMUTEXNAME);

	if (!singletonEventHandle)
	{
		singletonEventHandle = CreateMutex(0, 0, APPMUTEXNAME);

		alreadyRunning = (::GetLastError() == ERROR_ALREADY_EXISTS ||
						  ::GetLastError() == ERROR_ACCESS_DENIED);
	}
	else
		alreadyRunning = True;

	return alreadyRunning;
}

void __fastcall TMainForm::acResultsRawExecute(TObject *Sender)                 // Resultado da leitura
{
	frxUserDataSetResultsRaw->RangeEndCount = ReadRawGrid->DataRowCount;
	frxReportResultsRaw->PrepareReport();
	frxReportResultsRaw->ShowPreparedReport();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::frxUserDataSetResultsRawCheckEOF(TObject *Sender, bool &Eof)
{
	if (frxUserDataSetResultsRaw->RecNo >= frxUserDataSetResultsRaw->RangeEndCount)
		Eof = True;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::frxUserDataSetResultsRawGetValue(const UnicodeString VarName, Variant &Value)  //adicionar sample ID e subject ID
{
	if (VarName == "PlateName")
	{
		Value = ReadRawGrid->Cells[colReadRawPlateName->Position][frxUserDataSetResultsRaw->RecNo];
		return;
	}

	if ("RawCoord" == VarName)
	{
		Value = ReadRawGrid->Cells[colReadRawCoord->Position][frxUserDataSetResultsRaw->RecNo];
		return;
	}

	if ("WellID" == VarName)
	{
		Value = ReadRawGrid->Cells[colReadWellID->Position][frxUserDataSetResultsRaw->RecNo];
		return;
	}

	if ("RawType" == VarName)
	{
		Value = ReadRawGrid->Cells[colReadRawType->Position][frxUserDataSetResultsRaw->RecNo];
		return;
	}

	if ("RawValue" == VarName)
	{
		Value = ReadRawGrid->Cells[colReadRawValue->Position][frxUserDataSetResultsRaw->RecNo];
		return;
	}

	if ("RawBlankReduced" == VarName)
	{
		Value = ReadRawGrid->Cells[colReadRawBlankReducedValue->Position][frxUserDataSetResultsRaw->RecNo];
		return;
	}

	if ("PostProcessedValue" == VarName)
	{
		Value = ReadRawGrid->Cells[colPostprocessedValue->Position][frxUserDataSetResultsRaw->RecNo];
		return;
	}

	if ("StdDeviation" == VarName)
	{
		Value = ReadRawGrid->Cells[colStdDeviation->Position][frxUserDataSetResultsRaw->RecNo];
		return;
	}

	if ("CoefVariation" == VarName)
	{
		Value = ReadRawGrid->Cells[colCoefVariation->Position][frxUserDataSetResultsRaw->RecNo];
		return;
	}

	if ("RawInterpreted" == VarName)
	{
		Value = ReadRawGrid->Cells[colReadRawInterpretValue->Position][frxUserDataSetResultsRaw->RecNo];
		return;
	}

	if ("RawTimeStamp" == VarName)
	{
		if (ReadRawGrid->Cells[colReadRawTimestampValue->Position][frxUserDataSetResultsRaw->RecNo].IsNull())
			return;

		Value = ReadRawGrid->Cells[colReadRawTimestampValue->Position][frxUserDataSetResultsRaw->RecNo].IsNull();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::frxUserDataSetUnknowsCheckEOF(TObject *Sender, bool &Eof)
{
	if (frxUserDataSetUnknows->RecNo >= frxUserDataSetUnknows->RangeEndCount)
		Eof = True;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::frxUserDataSetUnknowsGetValue(const UnicodeString VarName, Variant &Value)
{
	if ("PlateName" == VarName)
	{
		Value = unknownsGrid->Cells[colUnknownPlateName->Position][frxUserDataSetUnknows->RecNo];
		return;
	}

	if ("Position" == VarName)
	{
		Value = unknownsGrid->Cells[colUnknownCoord->Position][frxUserDataSetUnknows->RecNo];
		return;
	}

	if ("ID" == VarName)
	{
		Value = unknownsGrid->Cells[colUnknownWellID->Position][frxUserDataSetUnknows->RecNo];
		return;
	}

	if ("Absorbance" == VarName)
	{
		Value = unknownsGrid->Cells[colUnknownPosProcessValue->Position][frxUserDataSetUnknows->RecNo];
		return;
	}

	if ("Concentration" == VarName)
	{
		Value = unknownsGrid->Cells[colUnknownConcentrationValue->Position][frxUserDataSetUnknows->RecNo];
		return;
	}

	if ("StdDeviation" == VarName)
	{
		Value = unknownsGrid->Cells[colUnknownStdDev->Position][frxUserDataSetUnknows->RecNo];
		return;
	}

	if ("CoefVariation" == VarName)
	{
		Value = unknownsGrid->Cells[colUnknownCoefVar->Position][frxUserDataSetUnknows->RecNo];
		return;
	}

	if ("Interpret" == VarName)
	{
		Value = unknownsGrid->Cells[colUnknownInterpretValue->Position][frxUserDataSetUnknows->RecNo];
		return;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::acResultUnknowsExecute(TObject *Sender)      // exportar Relatório de Desconhecidos
{
	frxUserDataSetUnknows->RangeEndCount = unknownsGrid->DataRowCount;
	frxReportUnknows->PrepareReport();
	frxReportUnknows->ShowPreparedReport();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::lmdstdValuesGridChange(TObject *Sender, TLMDGridChangeFlags AChangedFlags)
{
	if (colStdValue && lmdstdValuesGrid->CurrentColumn != colStdValue->Position)
        lmdstdValuesGrid->CurrentColumn = colStdValue->Position;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbCurveTypesChange(TObject *Sender)
{
	cbChartScale->ItemIndex = 0;

    if (cbCurveTypes->ItemIndex != mCurveTypes)
        mCurveTypes = cbCurveTypes->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::acAboutExecute(TObject *Sender)
{
	__try
	{
		FrmAbout = new TFrmAbout(this);
		FrmAbout->ShowModal();
	}
	__finally
	{
		FrmAbout->Free();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CalculateForReplicas(const TWellType type)
{
	WellMatrixList& wellMatrixListRef = *TWellMatrixSingleton::instance();

	for (WellMatrixList::size_type matIndex = 0; matIndex < wellMatrixListRef.size(); matIndex++)
	{
		WellList wl;
        wellMatrixListRef[matIndex].filterWellsByType(type, wl);

		if (wl.empty())
			continue;

	    std::sort(wl.begin(), wl.end());

        WellList::size_type unElements = wl.size();
        WellList::iterator last = std::unique(wl.begin(), wl.end());

        unElements = std::distance(wl.begin(), last);

        wl.resize(unElements);

        if (unElements < 1)
            continue;

		for (WellList::iterator cit = wl.begin(); cit != wl.end(); cit++)
		{
			WellListPointers wlr = wellMatrixListRef[matIndex].getAllReplicas(*cit);

            Double accumulated = 0;

            std::unique_ptr<Double> replicasValues(new Double[wlr.size()]);

            for (WellListPointers::iterator it = wlr.begin(); it != wlr.end(); ++it)
			{
				WellListPointers::size_type idxElement = std::distance(wlr.begin(), it);

				accumulated += (*it)->RawBlankReducedValue;
				Double rawBlankReduced = (*it)->RawBlankReducedValue;
				replicasValues.get()[idxElement] = rawBlankReduced;
			}

            Double avg = accumulated / std::max<Double>(wl.size(), 1.0);

            Double stdDeviation = 0, coefVariation = 0;

            if (wlr.size()-1)
			{
				Integer numElements = std::distance(wlr.begin(), wlr.end());

				stdDeviation = StdDev(replicasValues.get(), numElements-1);
                coefVariation = stdDeviation / std::max<Double>(avg, 0.00001f);
            }

            std::vector<Double> arrayValues;

            for (WellListPointers::size_type i = 0; i < wl.size(); i++)
                arrayValues.push_back(replicasValues.get()[i]);

			Double minValue = 0;
			Double maxValue = 0;
			double NaN = std::numeric_limits<double>::quiet_NaN();
			if (!arrayValues.empty()) {
				minValue = maxValue = arrayValues[0];
				for (size_t i = 1; i < arrayValues.size(); ++i) {
					double tmp = arrayValues[i];
					if (tmp = -NaN || tmp == NaN)
						continue;
					minValue = std::min(minValue, tmp);
					maxValue = std::max(maxValue, tmp);
				}
			}
            for (WellListPointers::iterator it = wlr.begin(); it != wlr.end(); it++)
            {
                (*it)->StdDeviation = stdDeviation;
                (*it)->CoefVariation = coefVariation;
                (*it)->MinimumValue = minValue;
				(*it)->MaximumValue = maxValue;
            }
        }
    }
}

void __fastcall TMainForm::acExperimentImportCalibrationExecute(TObject *Sender)
{
	WellMatrixList& wellMatrixListRef = *TWellMatrixSingleton::instance();

    WellList wl;

    wellMatrixListRef.front().filterWellsByType(TWellType::wlConcentrationStd, wl);

    if (!wl.empty())
    {
		TaskMessageDlg(TEXT("Carregamento da curva de calibração"),
					   TEXT("Não é permitido importar a curva de calibração em placas que contenham \"Padrões\".\n")
                       TEXT("Para continuar, remova os padrões da placa e tente novamente."),
                       mtWarning,
                       TMsgDlgButtons() << mbOK, 0);

        return;
    }

	const String LoccusDataName("Loccus Biotecnologia");
	const String AppDataDirName = TPath::GetFileNameWithoutExtension(Application->ExeName);
	String UserAppData = GetEnvironmentVariable("APPDATA");
	String PublicAppData = GetEnvironmentVariable("PUBLIC");

//    String AppDataDir = UserAppData + TEXT("\\") + LoccusDataName + TEXT("\\") + AppDataDirName;
	String AppDataDir = PublicAppData + TEXT("\\") + LoccusDataName + TEXT("\\") + AppDataDirName;

//	ProfileTypeDialog->Execute();
//
//	if (ProfileTypeDialog->ResultButtonId == 200)
//		AppDataDir = PublicAppData + TEXT("\\") + LoccusDataName + TEXT("\\") + AppDataDirName;
//
	if (!DirectoryExists(AppDataDir))
		MyDataModule->CreateDirectoryRecursively(AppDataDir);

	ForceCurrentDirectory = False;

	TStringList *encodings = new TStringList();
	encodings->AddObject("Ascii", TEncoding::ASCII);
	encodings->AddObject("Unicode", TEncoding::Unicode);
	encodings->AddObject("UTF-8", TEncoding::UTF8);

	TOpenTextFileDialog *FileOpenDialog = new TOpenTextFileDialog(this);

	FileOpenDialog->Title = TEXT("Carregar curva de calibração.");
	FileOpenDialog->Filter = TEXT("Arquivo de experimento (*.expr)|*.expr");
	FileOpenDialog->DefaultExt = TEXT(".expr");
	FileOpenDialog->InitialDir = AppDataDir;
	FileOpenDialog->Encodings->Assign(encodings);

	if (!FileOpenDialog->Execute(this->Handle))
	{
		FileOpenDialog->Free();
		return;
	}

	String experimentName = FileOpenDialog->FileName;

	FileOpenDialog->Free();

	TXMLDocument *xmlDoc = MyDataModule->XMLDocument;
	xmlDoc->LoadFromFile(experimentName);

	_di_IXMLNode ExperimentNode = xmlDoc->ChildNodes->FindNode("Experiment");

	if (!ExperimentNode)
	{
		TaskMessageDlg(TEXT("Carregamento da curva de calibração"),
					   TEXT("Formato do arquivo inválido ou corrompido. Tag \"Experiment\" não encontrada."),
					   mtError,
					   TMsgDlgButtons() << mbOK, 0);

		return;
	}

	_di_IXMLNode CalibrationNode = ExperimentNode->ChildNodes->FindNode("CalibrationCurve");

	if (!CalibrationNode)
	{
		TaskMessageDlg(TEXT("Carregamento da curva de calibração"),
					   TEXT("O experimento não contém curva de calibração."),
					   mtError,
					   TMsgDlgButtons() << mbOK, 0);

		return;
	}

	_di_IXMLNode TimestampNode = CalibrationNode->ChildNodes->FindNode("CreationDate");

	if (!TimestampNode)
	{
		TaskMessageDlg(TEXT("Carregamento da curva de calibração"),
					   TEXT("Formato do arquivo inválido ou corrompido. Tag \"CreationDate\" não encontrada."),
					   mtError,
					   TMsgDlgButtons() << mbOK, 0);

		return;
	}

	AskDialog->Title = TEXT("Carregamento da curva de calibração");
	AskDialog->Content = TEXT("A curva de calibração que está sendo importada foi criada em ") +
						 TimestampNode->Text +
						 TEXT(".\nOs resultados correm o risco de não serem precisos, deseja continuar?");

	AskDialog->Execute();

	if (AskDialog->ResultButtonId != 200)
		return;

	mCalibrationCurve.reset(new CalibrationData());

	if (!LoadCurveBranch(CalibrationNode))
		return;

	Application->Title += String(" (*)");

	cbCurveTypes->ItemIndex = mCalibrationCurve->curveType;

    mCurveImported = True;
}
//---------------------------------------------------------------------------

Boolean __fastcall TMainForm::LoadCurveBranch(_di_IXMLNode Node)
{
    mCalibrationCurve->curveType = Node->Attributes[TEXT("Type")];

    _di_IXMLNode parameters = Node->ChildNodes->FindNode(TEXT("Parameters"));

    _di_IXMLNode qtdParametersNode = parameters->ChildNodes->FindNode(TEXT("Quantity"));
    mCalibrationCurve->qtdParameters = qtdParametersNode->GetNodeValue();

    _di_IXMLNode valuesNode = parameters->ChildNodes->FindNode(TEXT("Values"));

    for (Integer i = 0; i < mCalibrationCurve->qtdParameters; i++)
    {
        Double paramValue = valuesNode->ChildValues[i];

        mCalibrationCurve->parameters.push_back(paramValue);
    }

    _di_IXMLNode stdValuesNode = Node->ChildNodes->FindNode(TEXT("StandardValues"));
    _di_IXMLNode stdValuePairNode = stdValuesNode->ChildNodes->First();
    while (stdValuePairNode)
    {
        Double stdValue = 0, rawValue = 0;

        _di_IXMLNode node = stdValuePairNode->ChildNodes->FindNode(TEXT("RawValue"));
        rawValue = node->GetNodeValue();

        node = stdValuePairNode->ChildNodes->FindNode(TEXT("StdValue"));
        stdValue = node->GetNodeValue();

        std::pair<Double, Double> p(rawValue, stdValue);
        mCalibrationCurve->stdValues.push_back(p);

        stdValuePairNode = stdValuePairNode->NextSibling();
    }

	_di_IXMLNode creationNode = Node->ChildNodes->FindNode("CreationDate");
    if (!TryStrToDateTime(creationNode->Text, mCalibrationCurve->timestamp))
    {
		TaskMessageDlg(TEXT("Carregamento de curva de calibração"),
					   TEXT("Formato do arquivo inválido ou corrompido. Tag \"CreationDate\" inválido."),
                       mtError,
                       TMsgDlgButtons() << mbOK, 0);

        return False;
    }

    return True;
}

void __fastcall TMainForm::CreateCurveBranch(_di_IXMLNode Node)
{
	_di_IXMLNode curveNode = Node->AddChild(TEXT("CalibrationCurve"));

	curveNode->SetAttribute(TEXT("Type"), mCurveTypes);

	_di_IXMLNode curveParams = curveNode->AddChild(TEXT("Parameters"));

	_di_IXMLNode quantityNode = curveParams->AddChild(TEXT("Quantity"));
	quantityNode->SetNodeValue(mCalibrationCurve->qtdParameters);

	_di_IXMLNode valuesNode = curveParams->AddChild(TEXT("Values"));

	for (Integer i = 0; i < mCalibrationCurve->qtdParameters; i++)
	{
		String paramName((Char)(i + 'A'));
		valuesNode->AddChild(paramName);
		valuesNode->ChildValues[paramName] = mCalibrationCurve->parameters[i];
	}

	_di_IXMLNode stdsNode = curveNode->AddChild(TEXT("StandardValues"));

	WellMatrixList& wellMatrixListRef = (*TWellMatrixSingleton::instance());

	WellList conclp;
    wellMatrixListRef.front().filterWellsByType(TWellType::wlConcentrationStd, conclp);

    std::sort(conclp.begin(), conclp.end());

	WellList::iterator last = std::unique(conclp.begin(), conclp.end());

	WellList::size_type unElements = std::distance(conclp.begin(), last);
	conclp.resize(unElements);

	for (WellList::const_iterator it = conclp.begin(); it != conclp.end(); it++)
	{
		_di_IXMLNode stdValues = stdsNode->AddChild(TEXT("Values"));

		_di_IXMLNode rawValue = stdValues->AddChild(TEXT("RawValue"));
		rawValue->SetNodeValue(it->RawValue);

		_di_IXMLNode stdValue = stdValues->AddChild(TEXT("StdValue"));
		stdValue->SetNodeValue(it->StdValue);
	}

	_di_IXMLNode creationNode = curveNode->AddChild("CreationDate");
	//creationNode->SetNodeValue(mCalibrationCurve->timestamp.DateTimeString());                 //TODO: CORRIGIR VALORES EXPORTADOS
	creationNode->SetNodeValue(Now());
	}

void __fastcall TMainForm::acLoadExperimentExecute(TObject *Sender)
{
	const String LoccusDataName("Loccus Biotecnologia");
	const String AppDataDirName = TPath::GetFileNameWithoutExtension(Application->ExeName);
	String UserAppData = GetEnvironmentVariable("APPDATA");
	String PublicAppData = GetEnvironmentVariable("PUBLIC");

	String AppDataDir = PublicAppData + TEXT("\\") + LoccusDataName + TEXT("\\") + AppDataDirName;
//    String AppDataDir = UserAppData + TEXT("\\") + LoccusDataName + TEXT("\\") + AppDataDirName;
//
//	ProfileTypeDialog->Execute();
//
//	if (ProfileTypeDialog->ResultButtonId == 200)
//		AppDataDir = PublicAppData + TEXT("\\") + LoccusDataName + TEXT("\\") + AppDataDirName;

	if (!DirectoryExists(AppDataDir))
        MyDataModule->CreateDirectoryRecursively(AppDataDir);

    ForceCurrentDirectory = False;

    TStringList *encodings = new TStringList();
    encodings->AddObject("Ascii", TEncoding::ASCII);
    encodings->AddObject("Unicode", TEncoding::Unicode);
    encodings->AddObject("UTF-8", TEncoding::UTF8);

    TOpenTextFileDialog *FileOpenDialog = new TOpenTextFileDialog(this);

    FileOpenDialog->Title = TEXT("Carregar Experimento");
    FileOpenDialog->Filter = TEXT("Arquivo de experimento (*.expr)|*.expr");
    FileOpenDialog->DefaultExt = TEXT(".expr");
    FileOpenDialog->InitialDir = AppDataDir;
    FileOpenDialog->Encodings->Assign(encodings);

    if (!FileOpenDialog->Execute(this->Handle))
    {
        FileOpenDialog->Free();
        return;
    }

	m_ExperimentName = FileOpenDialog->FileName;

	FileOpenDialog->Free();

	 WideChar decSeparator = FormatSettings.DecimalSeparator;
	WideChar thSeparator  = FormatSettings.ThousandSeparator;

	if (mpAppConfig->DecimalSeparator != FormatSettings.DecimalSeparator)
		FormatSettings.DecimalSeparator = mpAppConfig->DecimalSeparator;

	if (mpAppConfig->ThousandSeparator != FormatSettings.ThousandSeparator)
		FormatSettings.ThousandSeparator = mpAppConfig->ThousandSeparator;

	InitAll();

    TXMLDocument *xmlDoc = MyDataModule->XMLDocument;
    xmlDoc->LoadFromFile(m_ExperimentName);

	_di_IXMLNode ExperimentNode = xmlDoc->ChildNodes->FindNode("Experiment");

    if (!ExperimentNode)
    {
		TaskMessageDlg("Carregamento de Experimento",
                       "Formato do arquivo inválido ou corrompido. Tag \"Experiment\" não encontrada.",
                       mtError,
                       TMsgDlgButtons() << mbOK, 0);

        return;
    }

    _di_IXMLNode ProtoNode = ExperimentNode->ChildNodes->FindNode("Protocol");

    if (!ProtoNode)
    {
		TaskMessageDlg("Carregamento de Experimento",
                       "Formato do arquivo inválido ou corrompido. Tag \"Protocol\" não encontrada.",
                       mtError,
                       TMsgDlgButtons() << mbOK, 0);

        return;
    }

    LoadSetupBranch(ProtoNode);

	_di_IXMLNode Results = ExperimentNode->ChildNodes->FindNode("Results");
	LoadResultsBranch(Results);

	TTreeNode *platesNode = getNode(TEXT("Placas"));

	for (Integer i = tabAbsorbanceScrollBox->ControlCount-1; i >= 0; --i)
		tabAbsorbanceScrollBox->Controls[i]->Free();

	for (Integer i = tabConcentrationScrollBox->ControlCount-1; i >= 0; --i)
		tabConcentrationScrollBox->Controls[i]->Free();

	for (Integer i = tabQualitativeScrollBox->ControlCount-1; i >= 0; --i)
		tabQualitativeScrollBox->Controls[i]->Free();

	curveSerie->Clear();
	pointsSerie->Clear();

	DoProcessResults();

	TTreeNode *tNode = platesNode->getFirstChild();
	_di_IXMLNode pNode = ProtoNode->ChildNodes->FindNode(TEXT("Plates"))->ChildNodes->First();

	Integer controlIndex = 0;

	while (tNode)
	{
		String plateName = pNode->Attributes[TEXT("Name")];

		if (tNode->Text != plateName)
		{
			tNode->Text = plateName;

			TWellResult *pwe = dynamic_cast<TWellResult *>(tabAbsorbanceScrollBox->Controls[controlIndex]);
			pwe->lbPlateCaption->Caption = tNode->Text;

			pwe = dynamic_cast<TWellResult *>(tabConcentrationScrollBox->Controls[controlIndex]);
			pwe->lbPlateCaption->Caption = tNode->Text;

			pwe = dynamic_cast<TWellResult *>(tabQualitativeScrollBox->Controls[controlIndex]);
			pwe->lbPlateCaption->Caption = tNode->Text;

			controlIndex++;
		}

		tNode = tNode->getNextSibling();
		pNode = pNode->NextSibling();
	}

	OptExperimentExportCSV->Enabled = True;
	OptExportarValoresBrutos->Enabled = True;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::acLoadProtocolExecute(TObject *Sender)
{
	const String LoccusDataName("Loccus Biotecnologia");
	const String AppDataDirName = TPath::GetFileNameWithoutExtension(Application->ExeName);
	String UserAppData = GetEnvironmentVariable("APPDATA");
	String PublicAppData = GetEnvironmentVariable("PUBLIC");

	String AppDataDir = PublicAppData + TEXT("\\") + LoccusDataName + TEXT("\\") + AppDataDirName;
//	String AppDataDir = UserAppData + TEXT("\\") + LoccusDataName + TEXT("\\") + AppDataDirName;
//
//	ProfileTypeDialog->Execute();
//
//	if (ProfileTypeDialog->ResultButtonId == 200)
//		AppDataDir = PublicAppData + TEXT("\\") + LoccusDataName + TEXT("\\") + AppDataDirName;

	if (!DirectoryExists(AppDataDir))
		MyDataModule->CreateDirectoryRecursively(AppDataDir);

	ForceCurrentDirectory = False;

	TStringList *encodings = new TStringList();
	encodings->AddObject("Ascii", TEncoding::ASCII);
	encodings->AddObject("Unicode", TEncoding::Unicode);
	encodings->AddObject("UTF-8", TEncoding::UTF8);

	TOpenTextFileDialog *FileOpenDialog = new TOpenTextFileDialog(this);
	FileOpenDialog->Title = TEXT("Carregar Protocolo");
	FileOpenDialog->Filter = TEXT("Arquivo de protocolo (*.ptrl)|*.ptrl");
	FileOpenDialog->DefaultExt = TEXT(".ptrl");
	FileOpenDialog->InitialDir = AppDataDir;
	FileOpenDialog->Encodings->Assign(encodings);

	if (!FileOpenDialog->Execute(this->Handle))
	{
		FileOpenDialog->Free();

		return;
	}

	String protoName = FileOpenDialog->FileName;

	FileOpenDialog->Free();

	InitAll();

	TXMLDocument *xmlDoc = MyDataModule->XMLDocument;
	xmlDoc->LoadFromFile(protoName);

	_di_IXMLNode ProtoNode = xmlDoc->ChildNodes->FindNode("Protocol");

	if (!ProtoNode)
	{
		TaskMessageDlg("Carregamento de Protocolo",
					   "Formato do arquivo inválido ou corrompido. Tag \"Protocol\" não encontrada.",
					   mtError,
					   TMsgDlgButtons() << mbOK, 0);

		return;
	}

	LoadSetupBranch(ProtoNode);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::acSaveProtocolExecute(TObject *Sender)
{
	const String LoccusDataName("Loccus Biotecnologia");
	const String AppDataDirName = TPath::GetFileNameWithoutExtension(Application->ExeName);
    String UserAppData = GetEnvironmentVariable("APPDATA");
    String PublicAppData = GetEnvironmentVariable("PUBLIC");

	String AppDataDir = PublicAppData + TEXT("\\") + LoccusDataName + TEXT("\\") + AppDataDirName;
//	String AppDataDir = UserAppData + TEXT("\\") + LoccusDataName + TEXT("\\") + AppDataDirName;
//
//	ProfileTypeDialog->Execute();
//
//	if (ProfileTypeDialog->ResultButtonId == 200)
//		AppDataDir = PublicAppData + TEXT("\\") + LoccusDataName + TEXT("\\") + AppDataDirName;

	if (!DirectoryExists(AppDataDir))
		MyDataModule->CreateDirectoryRecursively(AppDataDir);

	ForceCurrentDirectory = False;

    TStringList *encodings = new TStringList();
    encodings->AddObject("Ascii", TEncoding::ASCII);
    encodings->AddObject("Unicode", TEncoding::Unicode);
    encodings->AddObject("UTF-8", TEncoding::UTF8);

    TSaveTextFileDialog *FileSaveDialog = new TSaveTextFileDialog(this);
    FileSaveDialog->Title = TEXT("Salvar Protocolo");
    FileSaveDialog->Filter = TEXT("Arquivo de protocolo (*.ptrl)|*.ptrl");
    FileSaveDialog->DefaultExt = TEXT(".ptrl");
    FileSaveDialog->InitialDir = AppDataDir;
    FileSaveDialog->Encodings->Assign(encodings);

    if (!FileSaveDialog->Execute(this->Handle))
    {
        FileSaveDialog->Free();
        return;
    }

    String protoName = FileSaveDialog->FileName;

    FileSaveDialog->Free();

    TXMLDocument *xmlDoc = MyDataModule->XMLDocument;
    xmlDoc->XML->Clear();

    xmlDoc->Active = True;
	xmlDoc->Version = "1.0";
    xmlDoc->Encoding = "utf-8";
    xmlDoc->StandAlone = "yes";

    _di_IXMLNode ProtoNode = xmlDoc->CreateElement("Protocol", "");
    xmlDoc->DocumentElement = ProtoNode;

	CreateSetupBranch(ProtoNode);


	if (FileExists(protoName))
		DeleteFile(protoName);

	xmlDoc->SaveToFile(protoName);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::acNewProtocolExecute(TObject *Sender)
{
	CurrentProtocol = -1;

	InitAll();

	pageControl->TabIndex = 0;
	treeview->Selected = getNode(0);

	AddPlateMenuItemClick(Sender);

	UpdateUi(True);

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::acSaveExperimentExecute(TObject *Sender)
{
	const String LoccusDataName("Loccus Biotecnologia");
	const String AppDataDirName = TPath::GetFileNameWithoutExtension(Application->ExeName);
    String UserAppData = GetEnvironmentVariable("APPDATA");
	String PublicAppData = GetEnvironmentVariable("PUBLIC");

//    String AppDataDir = UserAppData + TEXT("\\") + LoccusDataName + TEXT("\\") + AppDataDirName;
	String AppDataDir = PublicAppData + TEXT("\\") + LoccusDataName + TEXT("\\") + AppDataDirName;

//	ProfileTypeDialog->Execute();
//
//	if (ProfileTypeDialog->ResultButtonId == 200)
//		AppDataDir = PublicAppData + TEXT("\\") + LoccusDataName + TEXT("\\") + AppDataDirName;

	if (!DirectoryExists(AppDataDir))
		MyDataModule->CreateDirectoryRecursively(AppDataDir);

	ForceCurrentDirectory = False;

	TStringList *encodings = new TStringList();
	encodings->AddObject("Ascii", TEncoding::ASCII);
	encodings->AddObject("Unicode", TEncoding::Unicode);
	encodings->AddObject("UTF-8", TEncoding::UTF8);

	TSaveTextFileDialog *FileSaveDialog = new TSaveTextFileDialog(this);

	FileSaveDialog->Title = TEXT("Salvar Experimento");
    FileSaveDialog->Filter = TEXT("Arquivo de experimento (*.expr)|*.expr");
    FileSaveDialog->DefaultExt = TEXT(".expr");
    FileSaveDialog->InitialDir = AppDataDir;
    FileSaveDialog->Encodings->Assign(encodings);

    if (!FileSaveDialog->Execute(this->Handle))
    {
        FileSaveDialog->Free();
        return;
    }

	m_ExperimentName = FileSaveDialog->FileName;

	FileSaveDialog->Free();
   /*
	WideChar decSeparator = FormatSettings.DecimalSeparator;
	WideChar thSeparator  = FormatSettings.ThousandSeparator;

	if (mpAppConfig->DecimalSeparator != FormatSettings.DecimalSeparator)
		FormatSettings.DecimalSeparator = mpAppConfig->DecimalSeparator;

	if (mpAppConfig->ThousandSeparator != FormatSettings.ThousandSeparator)
		FormatSettings.ThousandSeparator = mpAppConfig->ThousandSeparator;
    */
    TXMLDocument *xmlDoc = MyDataModule->XMLDocument;
    xmlDoc->XML->Clear();

    xmlDoc->Active = True;
	xmlDoc->Version = "1.0";
    xmlDoc->Encoding = "utf-8";
    xmlDoc->StandAlone = "yes";

    _di_IXMLNode ExperimentNode = xmlDoc->CreateElement("Experiment", "");
    xmlDoc->DocumentElement = ExperimentNode;

    _di_IXMLNode ProtoNode = ExperimentNode->AddChild("Protocol");

	CreateSetupBranch(ProtoNode);

    _di_IXMLNode ResultsNode = ExperimentNode->AddChild("Results");

	CreateResultsBranch(ResultsNode);

	CreateCurveBranch(ExperimentNode);

	_di_IXMLNode node = ExperimentNode->AddChild("Author");
	node->SetNodeValue(mpAppConfig->UserLogin);

	node = ExperimentNode->AddChild("CreationDate");
	node->SetNodeValue(Now());

	if (FileExists(m_ExperimentName))
		DeleteFile(m_ExperimentName);

	xmlDoc->SaveToFile(m_ExperimentName);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::acExperimentExportCsvExecute(TObject *Sender)
{
	const String LoccusDataName("Loccus Biotecnologia");
	const String AppDataDirName = TPath::GetFileNameWithoutExtension(Application->ExeName);
	String UserAppData = GetEnvironmentVariable("APPDATA");
	String PublicAppData = GetEnvironmentVariable("PUBLIC");

	String AppDataDir = PublicAppData + TEXT("\\") + LoccusDataName + TEXT("\\") + AppDataDirName;

	ForceCurrentDirectory = False;

	TSaveTextFileDialog *FileSaveDialog = new TSaveTextFileDialog(this);
	FileSaveDialog->Title = TEXT("Exportar CSV");
	FileSaveDialog->Filter = TEXT("Arquivo de experimento CSV (*.expr.csv)|*.expr.csv");
	FileSaveDialog->DefaultExt = TEXT(".expr.csv");
	FileSaveDialog->InitialDir = AppDataDir;
	FileSaveDialog->FileName = m_ExperimentName;

	if (!FileSaveDialog->Execute(this->Handle))
	{
		FileSaveDialog->Free();
		return;
	}

	if (FileSaveDialog->FileName != m_ExperimentName)
		m_ExperimentName = FileSaveDialog->FileName;

	FileSaveDialog->Free();

	WideChar decSeparator = FormatSettings.DecimalSeparator;
	WideChar thSeparator  = FormatSettings.ThousandSeparator;

	if (mpAppConfig->DecimalSeparator != FormatSettings.DecimalSeparator)
		FormatSettings.DecimalSeparator = mpAppConfig->DecimalSeparator;

	if (mpAppConfig->ThousandSeparator != FormatSettings.ThousandSeparator)
		FormatSettings.ThousandSeparator = mpAppConfig->ThousandSeparator;

	std::vector<String> vectCSVList;

	std::unique_ptr<TStringList> csvStringList(new TStringList());
	csvStringList->Delimiter = ';';
	csvStringList->QuoteChar = '"';

	if (mpAppConfig->HeadersInCsv)         // configurações de exportação - RESULTADOS DE LEITURA
	{
		csvStringList->Add("Placa");
		csvStringList->Add("Posição");
		csvStringList->Add("Tipo");
		csvStringList->Add("Absorbância Bruta");
		csvStringList->Add("Absorbância Processada");
		csvStringList->Add("Concentração");
		csvStringList->Add("Desvio Padrão");
		csvStringList->Add("Coef. Variação");
		csvStringList->Add("Interpretação");
		csvStringList->Add("Momento Leitura");

		vectCSVList.push_back(csvStringList->DelimitedText);

		csvStringList->Clear();
	}

	WellMatrixList wellMatrixListRef = *TWellMatrixSingleton::instance();

	Integer rowPos = 0, plateIdx = 0;

	for (plateIdx = 0; plateIdx < wellMatrixListRef.size(); plateIdx++)
	   {
		for (Integer col = 0; col < m_elisaDeviceParams->PlateCols; col++)
		 {
				for (Integer row = 0; row < m_elisaDeviceParams->PlateRows; row++)
			   {
				   TWellMatrix& wm = wellMatrixListRef[plateIdx];
				 TWell& w = wm[row][col];

				 String wellInfo;
				  wellInfo.sprintf(TEXT("%c%d"), row + 'A', col + 1);

				  csvStringList->Add(getNode(plateIdx + 101)->Text); // Nome da placa
				  csvStringList->Add(wellInfo);                     // Informação da posição
				  csvStringList->Add(w.typeToString());             // Tipo do poço
				  csvStringList->Add(FloatToStrF(w.RawValue, ffFixed, 6, 3)); // Absorbância Bruta
				  csvStringList->Add(FloatToStrF(w.RawBlankReducedValue, ffFixed, 6, 3)); // Absorbância Processada
				  csvStringList->Add(FloatToStrF(w.ConcentrationValue, ffFixed, 6, 3)); // Concentração
				  csvStringList->Add(FloatToStrF(w.StdDeviation, ffFixed, 6, 3));       // Desvio Padrão
				  csvStringList->Add(FloatToStrF(w.CoefVariation, ffFixed, 3, 2));     // Coef. Variação
				  csvStringList->Add(VarToStr(w.Interpret));                           // Interpretação
				  csvStringList->Add(FormatDateTime("hh:nn:ss", w.Timestamp));         // Momento de Leitura

            vectCSVList.push_back(csvStringList->DelimitedText);
            csvStringList->Clear();
        }
    }
}

	LongWord fmOption = fmCreate | fmShareDenyWrite;

	if (FileExists(m_ExperimentName))
		DeleteFile(m_ExperimentName);

	TStreamWriter *fStream = new TStreamWriter(new TFileStream(m_ExperimentName, fmOption), TEncoding::UTF8, 1024);

	for (std::vector<String>::size_type i = 0; i < vectCSVList.size(); i++)
		fStream->WriteLine(vectCSVList[i]);

	fStream->Close();

	fStream->BaseStream->Free();
	fStream->Free();

	FormatSettings.DecimalSeparator = decSeparator;
	FormatSettings.ThousandSeparator = thSeparator;

	TaskMessageDlg(TEXT("Exportar CSV"),
				   TEXT("Experimento exportado com sucesso."),
				   mtInformation,
				   TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::acExportRawValuesExecute(TObject *Sender)
{
	using System::Sysutils::Format;

	const String LoccusDataName("Loccus Biotecnologia");
	const String AppDataDirName = TPath::GetFileNameWithoutExtension(Application->ExeName);
	String UserAppData = GetEnvironmentVariable("APPDATA");
	String PublicAppData = GetEnvironmentVariable("PUBLIC");
	String rawFileName;

	String AppDataDir = PublicAppData + TEXT("\\") + LoccusDataName + TEXT("\\") + AppDataDirName;

	ForceCurrentDirectory = False;

	TSaveTextFileDialog *FileSaveDialog = new TSaveTextFileDialog(this);
	FileSaveDialog->Title = TEXT("Exportar Dados Brutos");
	FileSaveDialog->Filter = TEXT("Arquivo RAW.CSV (*.raw.csv)|*.raw.csv");
	FileSaveDialog->DefaultExt = TEXT(".raw.csv");
	FileSaveDialog->InitialDir = AppDataDir;

	if (!FileSaveDialog->Execute(this->Handle))
	{
		FileSaveDialog->Free();
		return;
	}

	rawFileName = FileSaveDialog->FileName;
	FileSaveDialog->Free();

	LongWord fmOption = fmCreate | fmShareDenyWrite;

	// Se o arquivo já existe, deletamos para evitar sobrescrita errada
	if (FileExists(rawFileName))
		DeleteFile(rawFileName);

	// Abrir o arquivo uma única vez em modo de adição (fmOpenWrite | fmShareDenyWrite)
	TStreamWriter *fStream = new TStreamWriter(new TFileStream(rawFileName, fmCreate | fmShareDenyWrite), TEncoding::Unicode, 1024);

	WideChar decSeparator = FormatSettings.DecimalSeparator;
	WideChar thSeparator = FormatSettings.ThousandSeparator;

	if (mpAppConfig->DecimalSeparator != FormatSettings.DecimalSeparator)
		FormatSettings.DecimalSeparator = mpAppConfig->DecimalSeparator;

	if (mpAppConfig->ThousandSeparator != FormatSettings.ThousandSeparator)
		FormatSettings.ThousandSeparator = mpAppConfig->ThousandSeparator;

	WellMatrixList wellMatrixListRef = *TWellMatrixSingleton::instance();

	Integer rowPos = 0, plateIdx = 0;

	for (plateIdx = 0; plateIdx < wellMatrixListRef.size(); plateIdx++)
	{
		std::unique_ptr<TStringList> csvStringList(new TStringList());
		csvStringList->Delimiter = '\t';

		std::vector<String> vectCSVList;

		// Exportar dados da tabela
		for (Integer row = 0; row < m_elisaDeviceParams->PlateRows; row++)
		{
			for (Integer col = 0; col < m_elisaDeviceParams->PlateCols; col++)
			{
				TWellMatrix& wm = wellMatrixListRef[plateIdx];
				TWell& w = wm[row][col];

				csvStringList->Add(FloatToStrF(w.RawValue, ffFixed, 6, 3));
			}

			vectCSVList.push_back(csvStringList->DelimitedText);
			csvStringList->Clear();
		}

		// Adiciona as informações extras após a tabela
		String plateName = StringReplace(getNode(plateIdx + 101)->Text, " ", "_", TReplaceFlags() << rfReplaceAll);
		String author = mpAppConfig->UserLogin;
		String filter1 = "";
		String filter2 = "";

		if (cbFilter1 && cbFilter1->Items->Count && cbFilter1->ItemIndex < cbFilter1->Items->Count)
			filter1 = cbFilter1->Items->Strings[cbFilter1->ItemIndex];

		if (rbFilterDouble->Checked && cbFilter2 && cbFilter2->Items->Count)
			filter2 = cbFilter2->Items->Strings[cbFilter2->ItemIndex];

		vectCSVList.push_back(TEXT("Nome_da_Placa: ") + plateName);
		vectCSVList.push_back(TEXT("Autor: ") + author);
		vectCSVList.push_back(TEXT("Filtro1: ") + filter1);
		vectCSVList.push_back(TEXT("Filtro2: ") + filter2);

		// Adiciona data e hora formatados
		TDateTime tStamp = mCalibrationCurve->timestamp;
		vectCSVList.push_back(TEXT("Data: ") + tStamp.FormatString("yyyy/MM/dd"));
		vectCSVList.push_back(TEXT("Hora: ") + tStamp.FormatString("hh:nn:ss"));

		// Escreve no arquivo (sem reabrir em cada iteração!)
		for (std::vector<String>::size_type i = 0; i < vectCSVList.size(); i++)
			fStream->WriteLine(vectCSVList[i]);

		vectCSVList.clear();
	}

	// Fecha o arquivo após todo o loop
	fStream->Close();
	fStream->BaseStream->Free();
	fStream->Free();

	String info = Format(TEXT("Dados Brutos salvos com sucesso."), ARRAYOFCONST((rawFileName)));

	TaskMessageDlg(TEXT("Dados Brutos"),
				   info,
				   mtInformation,
				   TMsgDlgButtons() << mbOK, 0);
}



//---------------------------------------------------------------------------

void __fastcall TMainForm::stdValuesGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
	if (State.Contains(gdFixed) || ACol == 3)
	{
		String s = stdValuesGrid->Cells[ACol][ARow];

		TCanvas *canvas = stdValuesGrid->Canvas;

		canvas->Brush->Color = stdValuesGrid->FixedColor;
		canvas->FillRect(Rect);

		Integer pixelsTextWidth = canvas->TextWidth(s);
		Integer pixelsTextHeight = canvas->TextHeight(s);

		Integer textPosX = (Rect.Width() / 2 - pixelsTextWidth / 2);
		Integer textPosY = (Rect.Height() / 2 - pixelsTextHeight / 2);

		canvas->TextOut(Rect.Left + textPosX, Rect.Top + textPosY, s);

		return;
	}

	String s = stdValuesGrid->Cells[ACol][ARow];

	if (s.IsEmpty())
		return;

	TCanvas *canvas = stdValuesGrid->Canvas;

	canvas->FillRect(Rect);

	if (State.Contains(gdSelected))
		canvas->Brush->Color = clSkyBlue;

	if (State.Contains(gdFocused))
		canvas->DrawFocusRect(Rect);

	canvas->FillRect(Rect);

	Integer pixelsTextWidth = canvas->TextWidth(s);
	Integer pixelsTextHeight = canvas->TextHeight(s);

	Integer textPosX = (Rect.Width() / 2 - pixelsTextWidth / 2);
	Integer textPosY = (Rect.Height() / 2 - pixelsTextHeight / 2);

	canvas->TextOut(Rect.Left + textPosX, Rect.Top + textPosY, s);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::stdValuesGridSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
	if (ACol == 3)
	{
		CanSelect = False;
		return;
	}

	if (stdValuesGrid->EditorMode)
	{
		stdValuesGrid->EditorMode = False;

		if (m_editingCol != -1 && m_editingRow != -1)
		{
			stdValuesGridSetEditText(Sender, m_editingCol, m_editingRow, stdValuesGrid->Cells[m_editingCol][m_editingRow]);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::stdValuesGridGetEditText(TObject *Sender, int ACol, int ARow, UnicodeString &Value)
{
	for (Integer i = 0; i < stdValuesGrid->ControlCount; i++)
	{
		if (stdValuesGrid->Controls[i]->ClassName() == "TInplaceEdit")
		{
			TInplaceEdit *ie = dynamic_cast<TInplaceEdit *>(stdValuesGrid->Controls[i]);

			ie->Alignment = System::Classes::taCenter;
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::stdValuesGridEnter(TObject *Sender)
{
	m_editingCol = -1;
	m_editingRow = -1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::stdValuesGridExit(TObject *Sender)
{
	if (m_editingCol != -1 && m_editingRow != -1)
	{
		stdValuesGrid->Col = m_editingCol;
		stdValuesGrid->Row = m_editingRow;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::stdValuesGridSetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value)
{
	if (!stdValuesGrid->EditorMode)
	{
		try
		{
			Double v = Value.ToDouble();

			if (mCurveImported)
				return;

			WellMatrixList& wellMatrixListRef = *TWellMatrixSingleton::instance();

			Integer cellId = stdValuesGrid->Cells[1][ARow].ToInt();

			TWell w;

			w.PlateNumber = 0;
			w.ID = cellId;
			w.Type = TWellType::wlConcentrationStd;

			WellListPointers wl = wellMatrixListRef.front().getAllReplicas(w);

			if (!wl.empty())
			{
				for (WellListPointers::iterator it = wl.begin(); it < wl.end(); ++it)
					(*it)->StdValue = v;
			}
		}
		catch (const EConvertError& e)
		{
			TaskMessageDlg(TEXT("Valor não permitido"),
						   TEXT("Por favor verifique o separador decimal configurado."),
						   mtError,
						   TMsgDlgButtons() << mbOK, 0);

			stdValuesGrid->Col = m_editingCol;
			stdValuesGrid->Row = m_editingRow;
			stdValuesGrid->EditorMode = True;
			return;
		}

		m_editingCol = -1;
		m_editingRow = -1;

		return;
	}

	m_editingCol = ACol;
	m_editingRow = ARow;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::chbShakeModeChange(TObject *Sender)
{
	m_elisaDeviceParams->ShakeMode = static_cast<TElisaShakeMode>(chbShakeMode->ItemIndex);

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::chbReadSpeedChange(TObject *Sender)
{
	m_elisaDeviceParams->ReadSpeed = static_cast<TElisaReadSpeed>(chbReadSpeed->ItemIndex);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

