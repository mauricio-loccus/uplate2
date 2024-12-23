//---------------------------------------------------------------------------

#ifndef unDataModuleH
#define unDataModuleH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "LMDPNGImageList.hpp"
#include <Vcl.ImgList.hpp>
#include <IdCoder.hpp>
#include <IdCoder00E.hpp>
#include <IdCoder3to4.hpp>
#include <IdCoderUUE.hpp>
#include <Xml.Win.msxmldom.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Vcl.Dialogs.hpp>
#include <IdBaseComponent.hpp>
#include <Vcl.ExtDlgs.hpp>
#include "LMDBaseController.hpp"
#include "LMDCustomComponent.hpp"
#include "LMDMMButtonFaceController.hpp"
#include "ZylSerialPort.hpp"
#include "SDL_math2.hpp"
#include "LMDVistaDialogs.hpp"

#include <memory>

struct CalibrationData;

//---------------------------------------------------------------------------
class TMyDataModule : public TDataModule
{
__published:	// IDE-managed Components
	TIdEncoderUUE *IdEncoderUUE;
	TCurveFit *curveFit;
	TLMDPNGImageList *pngImageList;
    TXMLDocument *XMLDocument;
    TIdDecoderUUE *IdDecoderUUE;
    TZylSerialPort *ZylSerialPort;
	TLMDFileSaveDialog *FileSaveDialog;

private:	// User declarations
public:		// User declarations
	__fastcall TMyDataModule(TComponent* Owner);
	Boolean __fastcall CalcLinearCurveFit(CalibrationData& refCalibrationCurve);
	Boolean __fastcall CalcLinearCurveFitCrossOrigin(CalibrationData& refCalibrationCurve);
	Boolean __fastcall CalcLinearLogCurveFit(CalibrationData& refCalibrationCurve);
	Boolean __fastcall CalcQuadraticCurveFit(CalibrationData& refCalibrationCurve);
	Boolean __fastcall CalcLogitLogCurveFit(CalibrationData& refCalibrationCurve);
	Boolean __fastcall Calc4ParametersCurveFit(CalibrationData& refCalibrationCurve);
	Boolean __fastcall Calc5ParametersCurveFit(CalibrationData& refCalibrationCurve);
	Boolean __fastcall CalcCubicSplineCurveFit(CalibrationData& refCalibrationCurve);
	Boolean __fastcall CalcPointToPointCurveFit(CalibrationData& refCalibrationCurve);
    String __fastcall EncryptString(const String& decrypted);
    Boolean __fastcall CreateDirectoryRecursively(const String& dirPath);
};
//---------------------------------------------------------------------------
extern PACKAGE TMyDataModule *MyDataModule;
//---------------------------------------------------------------------------
#endif
