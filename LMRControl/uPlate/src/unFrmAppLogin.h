//---------------------------------------------------------------------------

#ifndef unFrmAppLoginH
#define unFrmAppLoginH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Data.DB.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <Data.DbxSqlite.hpp>
//---------------------------------------------------------------------------
class TFrmAppLogin : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *PasswordEdit;
	TButton *btnLogar;
	TButton *btnCancel;
	TComboBox *ComboBoxUserName;
	void __fastcall btnLogarClick(TObject *Sender);
	void __fastcall ComboBoxUserNameChange(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);

private:	// User declarations
	Integer userID;
    String userLogin;
    String userName;
    Boolean isRoot;

public:		// User declarations
	__fastcall TFrmAppLogin(TComponent* Owner);

	__property Integer UserID = {read = userID};
    __property String UserLogin = {read = userLogin};
    __property String UserName = {read = userName};
    __property Boolean IsSuperUser = {read = isRoot};
};

//---------------------------------------------------------------------------
extern PACKAGE TFrmAppLogin *FrmAppLogin;
//---------------------------------------------------------------------------
#endif
