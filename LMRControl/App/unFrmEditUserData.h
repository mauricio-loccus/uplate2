//---------------------------------------------------------------------------

#ifndef unFrmEditUserDataH
#define unFrmEditUserDataH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "LMDBaseControl.hpp"
#include "LMDBaseGraphicButton.hpp"
#include "LMDBaseGraphicControl.hpp"
#include "LMDCustomMMButton.hpp"
#include "LMDMMButton.hpp"

//---------------------------------------------------------------------------
class TFrmEditUserData : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TEdit *tedUserLogin;
    TCheckBox *chbIsSuperUser;
    TLabel *Label2;
    TEdit *tedUserName;
    TLabel *Label3;
    TEdit *tedUserSurname;
    TLabel *Label4;
    TEdit *tedUserPassword;
    TLabel *Label5;
    TEdit *tedUserPasswordConfirm;
    TLabel *Label6;
    TEdit *tedUserDept;
    TLMDMMButton *btnApply;
    TLMDMMButton *btnCancel;
    void __fastcall btnApplyClick(TObject *Sender);
    void __fastcall btnCancelClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
    String mUserLogin;
    Boolean mUserIsRoot;
    String mUserName;
    String mUserSurname;
    String mUserDept;
    String mUserPassword;
    Boolean mbInEditMode;

public:		// User declarations
    __fastcall TFrmEditUserData(TComponent* Owner, Boolean editMode = False);

    __property String UserLogin = {read = mUserLogin, write = setUserLogin};
    __property Boolean UserIsSuperUser = {read = mUserIsRoot, write = setUserIsRoot};
    __property String UserPassword = {read = mUserPassword, write = setUserPassword};
    __property String UserName = {read = mUserName, write = setUserName};
    __property String UserSurname = {read = mUserSurname, write = setUserSurname};
    __property String UserDept = {read = mUserDept, write = setUserDept};

private:
    void __fastcall setUserLogin(const String& userLogin);
    void __fastcall setUserIsRoot(Boolean isRoot);
    void __fastcall setUserPassword(const String& userPassword);
    void __fastcall setUserName(const String& userName);
    void __fastcall setUserSurname(const String& userSurname);
    void __fastcall setUserDept(const String& userDept);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmEditUserData *FrmEditUserData;
//---------------------------------------------------------------------------
#endif
