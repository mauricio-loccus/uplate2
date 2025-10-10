//---------------------------------------------------------------------------

#ifndef unFrmMainH
#define unFrmMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.RegularExpressions.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.ActnMenus.hpp>
#include <Vcl.ToolWin.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "LMDControl.hpp"
#include "LMDCustomControl.hpp"
#include "LMDCustomPanel.hpp"
#include "LMDCustomSheetControl.hpp"
#include "LMDPageControl.hpp"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include "LMDBaseControl.hpp"
#include "LMDBaseGraphicControl.hpp"
#include "LMDBaseImage.hpp"
#include "LMDCustomNImage.hpp"
#include "LMDGraphicControl.hpp"
#include "LMDNImage.hpp"
#include "LMDCustomBevelPanel.hpp"
#include "LMDCustomPanelFill.hpp"
#include "LMDCustomParentPanel.hpp"

#include "unWell.h"
#include "LMDCustomComponent.hpp"
#include "LMDCustomHint.hpp"
#include "LMDCustomShapeHint.hpp"
#include "LMDMessageHint.hpp"
#include "LMDNativeHint.hpp"
#include "LMDButtonControl.hpp"
#include "LMDCheckBox.hpp"
#include "LMDCustomCheckBox.hpp"
#include "LMDGrid.hpp"
#include "LMDHint.hpp"
#include <Vcl.Mask.hpp>
#include "LMDShapeHint.hpp"
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
#include "frxClass.hpp"
#include "frxExportPDF.hpp"
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include "SDL_math2.hpp"
#include <VCLTee.TeeSpline.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <Vcl.Samples.Spin.hpp>
#include "LMDBaseGraphicButton.hpp"
#include "LMDCustomMMButton.hpp"
#include "LMDMMButton.hpp"
#include "LMDCustomScrollBox.hpp"
#include "LMDListBox.hpp"
#include "LMDBaseEdit.hpp"
#include "LMDCustomEdit.hpp"
#include "LMDCustomExtSpinEdit.hpp"
#include "LMDCustomMaskEdit.hpp"
#include "LMDSpinEdit.hpp"
#include "LMDMaskEdit.hpp"
#include "LMDFloatRangeValidator.hpp"
#include "LMDHintErrorProvider.hpp"
#include "LMDVldBase.hpp"
#include "LMDScrollBox.hpp"
#include "LMDCheckGroup.hpp"
#include "LMDCustomButtonGroup.hpp"
#include "LMDCustomCheckGroup.hpp"
#include "LMDCustomGroupBox.hpp"
#include "LMDButtonPanel.hpp"
#include "LMDCustomToolBar.hpp"
#include "LMDToolBar.hpp"
#include <Vcl.Dialogs.hpp>

#include <Xml.XmlDoc.hpp>
#include <Xml.Xmlintf.hpp>
#include <Xml.Win.msxmldom.hpp>
#include <Xml.xmldom.hpp>
#include "LMDTaskDlg.hpp"
#include "frxExportBaseDialog.hpp"
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>

#include <boost/functional.hpp>
#include <list>
#include <memory>
#include <map>
#include <utility>
#include <vector>

#include "unWellMatrix.h"

#include "unCellOptions.h"
#include "unElisaDevice.h"
#include "unParams.h"
#include "unWellsEdit.h"

#include "LMEFunctionEvaluator.h"
#include "unWellResult.h"

#include "unDataModule.h"

#include "unConfig.h"

//---------------------------------------------------------------------------
typedef std::vector<Double> DoubleArray;

typedef std::pair<String, TPicture *> ResultPair;
typedef std::vector<ResultPair> ResultsVector;

enum class InternalMessages
{
    WM_PLATE_ADDED = WM_USER+1024
};

struct CalibrationData
{
    Word curveType;
	Word qtdParameters;
	std::vector<Double> parameters;
	std::vector< std::pair<Double, Double> > stdValues;
	TDateTime timestamp;

	CalibrationData() : curveType(0), qtdParameters(0), timestamp(-1) {}
};

class TMainForm : public TForm
{
	typedef TForm ancestor;

	friend class TMyDataModule;

__published:	// IDE-managed Components
	TTreeView *treeview;
	TSplitter *Splitter;
	TLMDPageControl *pageControl;
	TLMDTabSheet *tabStandards;
	TLMDTabSheet *tabUnknowns;
	TLMDTabSheet *tabCurveStd;
	TLMDGrid *lmdstdValuesGrid;
	TLMDTabSheet *tabParamRead;
	TLMDGridTextColumn *colReplicaNo;
	TLMDGridFloatColumn *colAbsorbance;
	TLMDGridFloatColumn *colStdValue;
	TGroupBox *grpShakeParams;
	TCheckBox *chkbShake;
	TLabel *Label1;
	TMaskEdit *meShakeDuration;
	TGroupBox *grpFilters;
	TLabel *lbFilter1;
	TComboBox *cbFilter1;
	TComboBox *cbFilter2;
	TLabel *lbFilter2;
	TComboBox *chbShakeIntensity;
	TLMDGrid *unknownsGrid;
	TLMDTabSheet *tabQuality;
	TLMDTabSheet *tabReadRAW;
	TLMDGrid *ReadRawGrid;

	TfrxReport *frxReportRawResult;
	TfrxUserDataSet *frxUserDataSetResults;
	TfrxPDFExport *frxPDFExport;
	TPopupMenu *treeviewMenu;
	TMenuItem *AddPlateMenuItem;
	TMenuItem *RemovePlateMenuItem;
	TChart *stdCurveChart;

	TLabel *lbR2;
	TLMDGridTextColumn *colPlateName;
	TMenuItem *RenamePlateMenuItem;
	TComboBox *cbChartScale;

	TChart *QualitativeZoneChart;
	TLineSeries *QZone1;
	TLineSeries *QZone2;

	TRadioButton *rbFilterSingle;
	TRadioButton *rbFilterDouble;
	TComboBox *cbCalcMethod;
	TLabel *lbCalcMode;
	TGroupBox *grpReadMode;
	TRadioButton *rbEndPoint;
	TRadioButton *rbKinetic;
	TGroupBox *grpKineticParams;
	TLMDListBox *lvKineticTimes;
	TLMDSpinEdit *spHours;
	TLMDSpinEdit *spMinutes;
	TLMDSpinEdit *spSeconds;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *lbKineticType;
	TComboBox *cbKineticType;
	TLabel *lbKineticReactionType;
	TComboBox *cbKineticReactionType;
	TComboBox *cbKineticRateType;
	TLabel *lbKineticRateType;
	TComboBox *cbKineticWindowType;
	TLabel *lbKineticWindowType;
	TLabel *lbKineticReadingsFromType;
	TComboBox *cbKineticReadingsFromType;
	TLabel *lbKineticBaselineReadings;
	TLabel *lbKineticChangeTimeType;
	TComboBox *cbKineticChangeTimeType;
	TLMDFloatRangeValidator *ThresholdFloatRangeValidator;
	TLMDHintErrorProvider *ThresholdHintErrorProvider;
	TLMDTabSheet *tabResults;
	TLMDPageControl *tabResultPageControl;
	TLMDTabSheet *tabResultAbsorbance;
	TLMDTabSheet *tabResultConcentration;
	TLMDTabSheet *tabResultQualitative;
	TScrollBox *tabAbsorbanceScrollBox;
	TScrollBox *tabConcentrationScrollBox;
	TScrollBox *tabQualitativeScrollBox;
	TLMDTabSheet *tabPlates;
	TLMDScrollBox *tabPlatesScrollBox;
	TLMDToolBar *toolbar;
	TStatusBar *StatusBar;
	TTimer *OneShotTimer;
	TLabel *lbUnity;
	TComboBox *cbUnity;
	TGroupBox *grpWaveLength;
	TLabel *Label12;
	TLabel *lbLambda2;
	TLabel *Label13;
	TRadioButton *rbSimpleLambda;
	TRadioButton *rbDoubleLambda;
	TSpinEdit *spLambda1;
	TSpinEdit *spLambda2;
	TComboBox *cbCalcMethod2;
	TLMDTaskDialog *ProfileTypeDialog;
	TSpinEdit *spKineticBaselineReadings;
	TLabel *lbKineticChangeThreshold;
	TSpinEdit *spKineticChangeThreshold;
	TLMDGridTextColumn *colReadWellID;
	TPanel *Panel1;
	TLabel *Label10;
	TComboBox *cbCurveTypes;
	TPanel *Panel2;
	TGroupBox *grpZona3;
	TLabel *Label8;
	TEdit *edZone3Interpret;
	TGroupBox *grpZona2;
	TLabel *Label6;
	TLabel *Label7;
	TEdit *edZone2Interpret;
	TEdit *edZone2Limit;
	TGroupBox *grpZona1;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *edZone1Interpret;
	TEdit *edZone1Limit;
	TLabel *lbZone2Limit;
	TLabel *lbZone1Limit;
	TComboFlat *cbOrigin;
	TLabel *Label9;
	TfrxReport *frxReportResultsRaw;
	TfrxUserDataSet *frxUserDataSetResultsRaw;
	TfrxReport *frxReportUnknows;
	TfrxUserDataSet *frxUserDataSetUnknows;
	TLMDTaskDialog *QuitAppDialog;
	TFastLineSeries *curveSerie;
	TPointSeries *pointsSerie;
	TLMDTaskDialog *AskDialog;

	TMainMenu *MainMenu;
	TMenuItem *File1;
	TMenuItem *OptUserLogin;
	TMenuItem *OptUserLogoff;
	TMenuItem *N2;
	TMenuItem *SMenuProtocol;
	TMenuItem *OptProtocolNew;
	TMenuItem *OptProtocolOpen;
	TMenuItem *OptProtocolSave;
	TMenuItem *N3;
	TMenuItem *SMenuExperiment;
	TMenuItem *OptExperimentLoad;
	TMenuItem *OptExperimentSave;
	TMenuItem *OptExperimentExportCSV;
	TMenuItem *OptExportarValoresBrutos;
	TMenuItem *ImportarCurvadeCalibrao1;
	TMenuItem *N1;
	TMenuItem *Exit1;
	TMenuItem *Relatrios1;
	TMenuItem *ResultadoPorPlaca;
	TMenuItem *RelatriodeDesconhecidos;
	TMenuItem *ResultadodaLeitura;
	TMenuItem *Configuraes1;
	TMenuItem *Preferncias1;
	TMenuItem *ConfiguraosFiltros1;
	TMenuItem *Ajuda1;
	TMenuItem *mnuAbout;
	TActionList *ActionList;
	TAction *acNewProtocol;
	TAction *acLoadProtocol;
	TAction *acSaveProtocol;
	TAction *acLoadExperiment;
	TAction *acConfPrefs;
	TAction *acAbout;
	TAction *actConnect;
	TAction *actDisconnect;
	TAction *actProgramRun;
	TAction *acRawResult;
	TAction *actOpenCloseDoor;
	TAction *acFiltersConfig;
	TAction *acResultsRaw;
	TAction *acResultUnknows;
	TAction *acSaveExperiment;
	TAction *acExperimentExportCsv;
	TAction *acExperimentImportCalibration;
	TAction *actExit;
	TAction *acExportRawValues;
	TAction *actInputLabels;

	TStringGrid *stdValuesGrid;
	TLabel *lblShakeMode;
	TComboBox *chbShakeMode;
	TComboBox *chbReadSpeed;
	TLabel *lblReadSpeed;

	TLMDGridTextColumn*  colReadRawPlateName;
	TLMDGridTextColumn*  colReadRawCoord;
	TLMDGridTextColumn*  colReadRawType;
	TLMDGridTextColumn*  colReadRawLabel;
	TLMDGridFloatColumn* colReadRawValue;
	TLMDGridFloatColumn* colReadRawBlankReducedValue;
	TLMDGridFloatColumn* colPostprocessedValue;
	TLMDGridFloatColumn* colStdDeviation;
	TLMDGridFloatColumn* colCoefVariation;
	TLMDGridTextColumn*  colReadRawInterpretValue;
	TLMDGridTextColumn*  colReadRawTimestampValue;

	TLMDGridTextColumn*  colUnknownPlateName;
	TLMDGridTextColumn*  colUnknownCoord;
	TLMDGridTextColumn*  colUnknownWellID;
	TLMDGridTextColumn*  colUnknownLabel;
	TLMDGridFloatColumn* colUnknownPosProcessValue;
	TLMDGridFloatColumn* colUnknownConcentrationValue;
	TLMDGridFloatColumn* colUnknownStdDev;
	TLMDGridFloatColumn* colUnknownCoefVar;
	TLMDGridTextColumn*  colUnknownInterpretValue;


	TMenuItem *MapadaPlaca1;


	void __fastcall actExitExecute(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall treeviewChange(TObject *Sender, TTreeNode *Node);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall chkbShakeClick(TObject *Sender);
	void __fastcall actConnectExecute(TObject *Sender);
	void __fastcall actDisconnectExecute(TObject *Sender);

	void __fastcall actProgramRunExecute(TObject *Sender);
	void __fastcall actLabelAssignment(TObject *Sender);
	void __fastcall chbShakeIntensityChange(TObject *Sender);
	void __fastcall cbFilter2Change(TObject *Sender);
	void __fastcall cbFilter1Change(TObject *Sender);

	void __fastcall OnLMR96ReadDone(TObject *Sender, const RawDataMatrix& matrix, const RawDataMatrix& matrixFilter2);
	void __fastcall acRawResultExecute(TObject *Sender);
	void __fastcall actOpenCloseDoorExecute(TObject *Sender);
	void __fastcall tabStandardsBeforeShowPage(TObject *Sender);
	void __fastcall colStdValueParse(TObject *Grid, TLMDGridColumn *Column, TLMDString &TextValue, Variant &ResultValue, bool &IsNull,
		  bool &ParsedOk, PLMDString PErrMsg, bool CanRaiseError);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall AddPlateMenuItemClick(TObject *Sender);
	void __fastcall RemovePlateMenuItemClick(TObject *Sender);
	void __fastcall treeviewMenuPopup(TObject *Sender);
	void __fastcall RenamePlateMenuItemClick(TObject *Sender);
	void __fastcall cbChartScaleChange(TObject *Sender);
	void __fastcall tabQualityBeforeShowPage(TObject *Sender);
	void __fastcall rbFilterDoubleClick(TObject *Sender);
	void __fastcall rbFilterSingleClick(TObject *Sender);
	void __fastcall cbCalcMethodChange(TObject *Sender);
	void __fastcall rbKineticClick(TObject *Sender);
	void __fastcall rbEndPointClick(TObject *Sender);
	void __fastcall btnAddClick(TObject *Sender);
	void __fastcall btnSubClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall lvKineticTimesSelect(TObject *Sender);
	void __fastcall spHoursChange(TObject *Sender);
	void __fastcall cbKineticTypeChange(TObject *Sender);
	void __fastcall cbKineticRateTypeChange(TObject *Sender);
	void __fastcall cbKineticWindowTypeChange(TObject *Sender);
	void __fastcall cbKineticReactionTypeChange(TObject *Sender);
	void __fastcall cbKineticReadingsFromTypeChange(TObject *Sender);
	void __fastcall cbKineticChangeTimeTypeChange(TObject *Sender);
	void __fastcall acFiltersConfigExecute(TObject *Sender);
	void __fastcall tabAbsorbanceScrollBoxMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
	void __fastcall tabConcentrationScrollBoxMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
	void __fastcall tabQualitativeScrollBoxMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
	void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
	void __fastcall toolbarButtonsClick(TObject *Sender, int index);
	void __fastcall OptUserLoginClick(TObject *Sender);
	void __fastcall OptUserLogoffClick(TObject *Sender);
	void __fastcall OneShotTimerTimer(TObject *Sender);
	void __fastcall acConfPrefsExecute(TObject *Sender);
	void __fastcall cbUnityChange(TObject *Sender);
	void __fastcall frxReportRawResultBeforePrint(TfrxReportComponent *Sender);
	void __fastcall frxUserDataSetResultsCheckEOF(TObject *Sender, bool &Eof);
	void __fastcall frxUserDataSetResultsGetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall spLambda1Change(TObject *Sender);
	void __fastcall spLambda2Change(TObject *Sender);
	void __fastcall rbSimpleLambdaClick(TObject *Sender);
	void __fastcall rbDoubleLambdaClick(TObject *Sender);
	void __fastcall spKineticChangeThresholdChange(TObject *Sender);
	void __fastcall spKineticBaselineReadingsChange(TObject *Sender);
	void __fastcall tabAbsorbanceScrollBoxResize(TObject *Sender);
	void __fastcall tabConcentrationScrollBoxResize(TObject *Sender);
	void __fastcall tabQualitativeScrollBoxResize(TObject *Sender);
	void __fastcall tabPlatesScrollBoxResize(TObject *Sender);
	void __fastcall acResultsRawExecute(TObject *Sender);
	void __fastcall frxUserDataSetResultsRawCheckEOF(TObject *Sender, bool &Eof);
	void __fastcall frxUserDataSetResultsRawGetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall frxUserDataSetUnknowsCheckEOF(TObject *Sender, bool &Eof);
	void __fastcall frxUserDataSetUnknowsGetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall acResultUnknowsExecute(TObject *Sender);
	void __fastcall lmdstdValuesGridChange(TObject *Sender, TLMDGridChangeFlags AChangedFlags);
	void __fastcall cbCurveTypesChange(TObject *Sender);
	void __fastcall acAboutExecute(TObject *Sender);
	void __fastcall acExperimentImportCalibrationExecute(TObject *Sender);
	void __fastcall acLoadExperimentExecute(TObject *Sender);
	void __fastcall acLoadProtocolExecute(TObject *Sender);
	void __fastcall acSaveProtocolExecute(TObject *Sender);
	void __fastcall acNewProtocolExecute(TObject *Sender);
	void __fastcall acSaveExperimentExecute(TObject *Sender);
	void __fastcall acExperimentExportCsvExecute(TObject *Sender);
	void __fastcall acExportRawValuesExecute(TObject *Sender);
	void __fastcall stdValuesGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);
	void __fastcall stdValuesGridSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall stdValuesGridGetEditText(TObject *Sender, int ACol, int ARow, UnicodeString &Value);
	void __fastcall stdValuesGridEnter(TObject *Sender);
	void __fastcall stdValuesGridExit(TObject *Sender);
	void __fastcall stdValuesGridSetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
	void __fastcall chbShakeModeChange(TObject *Sender);
	void __fastcall chbReadSpeedChange(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall AppMessage(tagMSG &Msg, bool &Handled);

public:
	void __fastcall LoginRequest();
	void __fastcall setDevice(PElisaDevice pDev);

private:	// User declarations
	enum TValueKind {
		Raw,
		Concentration
	};

	enum TSummarization {
		Unknown,
		Zero,
		Minimum,
		Maximum,
		Mean,
		Median
	};

	static HANDLE singletonEventHandle;

	bool   Initialized;
	String m_ExperimentName;
	System::Largeint CurrentProtocol;
	std::vector<Boolean> controlEnabledArray;

	TCellOptionsData cellOptions;
	TWellsShowOptionFlags showFlags;

	WellMatrixList::size_type currMatrix;

	PElisaDevice m_elisaDevice;
	ElisaParams *m_elisaDeviceParams;
	StlString commName;

	LME::FunctionEvaluator loccusEval;
	LME::Variable cp, cn;

	Integer resultsCount, mCurveTypes;

	HDEVNOTIFY hDevNotify;

	PAppConfig mpAppConfig;

	ResultsVector mResultsList;

	Boolean mWaveLengthControlsAdjusted;
	Boolean mFiltersControlsAdjusted;
	Boolean mCurveImported;

	Boolean m_deviceSimulated;

	std::unique_ptr<CalibrationData> mCalibrationCurve;

	Integer m_editingCol, m_editingRow;

	Boolean __fastcall UserLogon();
	Boolean __fastcall UserLogoff();

	void       __fastcall treeviewAddPlateNode(TTreeNodes *Node);
	void       __fastcall treeviewRemovePlateNode(TTreeNode *Node);
	TTreeNode* __fastcall getNode(Integer index, TTreeNode *parent = NULL) const;
	TTreeNode* __fastcall getNode(String name, TTreeNode *parent = NULL) const;
	void       __fastcall setNodeEnabled(TTreeNode *node, Boolean enabled = True);

	void __fastcall UpdatePlatesNames();

	double __fastcall WellSummarize(WellListPointers, TSummarization, TValueKind);

	void __fastcall DoProcessResults();
	void __fastcall DoProcessBlanks();
	void __fastcall DoProcessConcentrations();
	void __fastcall DoProcessCPnCNs();
	void __fastcall DoProcessQCs(WellList& ulp);

	void __fastcall PreviousDoProcessCPnCNs(TValueKind, WellMatrixList&);
	void __fastcall     NextDoProcessCPnCNs(TValueKind, WellMatrixList&);

	void __fastcall OldDoProcessCPnCNs();
	void __fastcall NewDoProcessCPnCNs();

	void __fastcall DoKineticRead(TWinControl *parent);
	void __fastcall DoNormalRead(TWinControl *parent);

	void __fastcall AddResultPlate(Integer plateNumber, const String& plateName);
	TPicture * __fastcall ResultPlateToImage(TWellResult *pWellResult);

	inline Boolean __fastcall UserLogged()
	{
		return mpAppConfig->UserID != -1;
	}

	void __fastcall WndProc(TMessage& message);

	void __fastcall FillResultsList();

	void __fastcall registerForDevicesMessages();
	virtual void __fastcall OnDeviceChange(TMessage& m);

	void __fastcall UpdateUi(Boolean enabled = False);


	void __fastcall InitAll();

	void __fastcall FillUnitiesComboBox();
	void __fastcall FillFiltersComboBox();

	void __fastcall InitSetup();
	void __fastcall LoadSetupBranch(_di_IXMLNode ProtoNode);
	void __fastcall CreateSetupBranch(_di_IXMLNode ProtoNode);

	void __fastcall LoadPlatesBranch(_di_IXMLNode PlatesNode);
	void __fastcall CreatePlatesBranch(_di_IXMLNode PatesNode);

	void __fastcall CreateCurveBranch(_di_IXMLNode Node);
	Boolean __fastcall LoadCurveBranch(_di_IXMLNode Node);

	void __fastcall InitLayout();

	void __fastcall InitCPCNParams();

	void __fastcall LoadResultsBranch(_di_IXMLNode ResultsNode);
	void __fastcall CreateResultsBranch(_di_IXMLNode ResultsNode);

	void __fastcall CalculateForReplicas(const TWellType type);

public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);

	void __fastcall UpdateLabels();

	static Boolean __fastcall AlreadyRunning();

BEGIN_MESSAGE_MAP
	MESSAGE_HANDLER(WM_DEVICECHANGE, TMessage, OnDeviceChange)
END_MESSAGE_MAP(TForm);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif

