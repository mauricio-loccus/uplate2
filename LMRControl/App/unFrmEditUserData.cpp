//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unFrmEditUserData.h"
#include "unDataModule.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LMDBaseControl"
#pragma link "LMDBaseGraphicButton"
#pragma link "LMDBaseGraphicControl"
#pragma link "LMDCustomMMButton"
#pragma link "LMDMMButton"
#pragma resource "*.dfm"
TFrmEditUserData *FrmEditUserData;
//---------------------------------------------------------------------------
__fastcall TFrmEditUserData::TFrmEditUserData(TComponent* Owner, Boolean editMode)
    : TForm(Owner), mbInEditMode(editMode)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmEditUserData::btnApplyClick(TObject *Sender)
{
    String password = MyDataModule->EncryptString(tedUserPassword->Text.Trim());
    String confirmPassword = MyDataModule->EncryptString(tedUserPasswordConfirm->Text.Trim());

    if (password != confirmPassword)
    {
        TaskMessageDlg(TEXT("Verificação da senha"),
                       TEXT("A senha é obrigatória e deve ser idêntica à senha de confirmação.\n"
                       "Por favor, tente novamente."),
                       mtError,
                       TMsgDlgButtons() << mbOK, 0);

        return;
    }

    mUserLogin = tedUserLogin->Text.Trim();
    mUserPassword = password;
    mUserName = tedUserName->Text.Trim();
    mUserSurname = tedUserSurname->Text.Trim();
    mUserIsRoot = chbIsSuperUser->Checked;
	mUserDept = tedUserDept->Text.Trim();

    ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TFrmEditUserData::btnCancelClick(TObject *Sender)
{
    ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TFrmEditUserData::setUserLogin(const String& userLogin)
{
    if (mUserLogin == userLogin)
        return;

    mUserLogin = userLogin;
}

void __fastcall TFrmEditUserData::setUserIsRoot(Boolean isRoot)
{
    if (mUserIsRoot == isRoot)
        return;

    mUserIsRoot = isRoot;
}

void __fastcall TFrmEditUserData::setUserPassword(const String& userPassword)
{
    if (mUserPassword == userPassword)
        return;

    mUserPassword = userPassword;
}

void __fastcall TFrmEditUserData::setUserName(const String& userName)
{
    if (mUserName == userName)
        return;

    mUserName = userName;
}

void __fastcall TFrmEditUserData::setUserSurname(const String& userSurname)
{
    if (mUserSurname == userSurname)
        return;

    mUserSurname = userSurname;
}

void __fastcall TFrmEditUserData::setUserDept(const String& userDept)
{
    if (mUserDept == userDept)
        return;

    mUserDept = userDept;
}

void __fastcall TFrmEditUserData::FormShow(TObject *Sender)
{
    tedUserLogin->Text = UserLogin;

    if (mbInEditMode)
    {
        tedUserPassword->Text = UserPassword;
        tedUserPasswordConfirm->Text = UserPassword;
    }

    tedUserName->Text = UserName.UpperCase();
    tedUserSurname->Text = UserSurname.UpperCase();
	tedUserDept->Text = UserDept.UpperCase();
	chbIsSuperUser->Checked = UserIsSuperUser;
}
//---------------------------------------------------------------------------

