//---------------------------------------------------------------------------

#ifndef unFrmConfigH
#define unFrmConfigH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "LMDControl.hpp"
#include "LMDCustomBevelPanel.hpp"
#include "LMDCustomControl.hpp"
#include "LMDCustomPanel.hpp"
#include "LMDCustomPanelFill.hpp"
#include "LMDCustomParentPanel.hpp"
#include "LMDCustomSheetControl.hpp"
#include "LMDPageControl.hpp"

#include "LMDButton.hpp"
#include "LMDCustomButton.hpp"
#include "LMDBaseControl.hpp"
#include "LMDBaseGraphicButton.hpp"
#include "LMDBaseGraphicControl.hpp"
#include "LMDCustomMMButton.hpp"
#include "LMDMMButton.hpp"
#include "LMDDBGrid.hpp"
#include "LMDGrid.hpp"
#include <Vcl.Grids.hpp>
#include "LMDDBBtn.hpp"
#include <Vcl.DBCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Data.DB.hpp>
#include <Data.DbxSqlite.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <Vcl.Menus.hpp>

#include <map>

#include "unConfig.h"

typedef std::map<String, Longint> UnitiesMap;

//---------------------------------------------------------------------------
class TFrmAppConfig : public TForm
{
__published:	// IDE-managed Components
    TLMDPageControl *pageControl;
    TLMDTabSheet *tabCSVOptions;
    TLabel *Label1;
    TEdit *teDecimalSeparator;
    TLabel *Label2;
    TEdit *teThousandSeparator;
    TLMDMMButton *btnApply;
    TLMDMMButton *btnCancel;
    TLMDTabSheet *tabEditUsers;
    TDBGrid *UserDBGrid;
    TDBNavigator *UserDBNavigator;
    TLMDTabSheet *tabUnities;
    TDBGrid *UnitiesDBGrid;
    TDBNavigator *UnitiesDBNavigator;
    TCheckBox *chbHeadersInCsv;
	TCheckBox *chbElisaSimulated;
    void __fastcall btnCancelClick(TObject *Sender);
    void __fastcall btnApplyClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall teThousandSeparatorKeyPress(TObject *Sender, System::WideChar &Key);
    void __fastcall teDecimalSeparatorKeyPress(TObject *Sender, System::WideChar &Key);
    void __fastcall UserDBNavigatorClick(TObject *Sender, TNavigateBtn Button);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall UnitiesDBNavigatorClick(TObject *Sender, TNavigateBtn Button);

private:	// User declarations
	PAppConfig mpAppConfig;
	UnitiesMap mUnitiesMap;

private:
	void __fastcall doKeyPressed(System::WideChar& Key);
	void __fastcall populateUnitiesMap();

public:		// User declarations
    __fastcall TFrmAppConfig(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmAppConfig *FrmAppConfig;
//---------------------------------------------------------------------------
#endif
