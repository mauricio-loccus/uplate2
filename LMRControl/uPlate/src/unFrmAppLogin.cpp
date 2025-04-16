//---------------------------------------------------------------------------

#include <vcl.h>
#include <memory>

#pragma hdrstop

#include "unFrmAppLogin.h"
#include "unDataModule.h"
#include "unDBModule.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmAppLogin *FrmAppLogin;

//---------------------------------------------------------------------------

__fastcall TFrmAppLogin::TFrmAppLogin(TComponent* Owner) : TForm(Owner), userID(-1)
{
}

//---------------------------------------------------------------------------

void __fastcall TFrmAppLogin::btnLogarClick(TObject *Sender)
{
	String Passwd = MyDataModule->EncryptString(PasswordEdit->Text.Trim());
	String SLogin = userName;

	Integer pos = userName.Pos(" (");
	if (pos != 0)
		SLogin = userName.SubString(1, pos-1);

	DBModule->UserQuery->ParamByName("pLogin")->AsString = SLogin;
	DBModule->UserQuery->Open();

	String fpasswd = DBModule->UserQuery->FieldByName("PASSWORD")->AsString;

	#ifdef _DEBUG
	String passwdDecripted = MyDataModule->IdDecoderUUE->DecodeString(fpasswd);
	#endif

	if (Passwd != fpasswd)  //Login Adminstrador | senha admin
	{
		MessageDlg("Senha incorreta, corrija e tente novamente.", mtWarning, TMsgDlgButtons() << mbOK, 0);

		ModalResult = mrNone;

		DBModule->UserQuery->Close();
		return;
	}

	userID = DBModule->UserQuery->FieldByName("ID")->AsInteger;
	userLogin = DBModule->UserQuery->FieldByName("LOGIN")->AsString;
	isRoot = DBModule->UserQuery->FieldByName("SUPERUSER")->AsInteger;

	DBModule->UserQuery->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFrmAppLogin::ComboBoxUserNameChange(TObject *Sender)
{
	userName = ComboBoxUserName->Text.Trim();
	btnLogar->Enabled = !userName.IsEmpty();
}
//---------------------------------------------------------------------------

void __fastcall TFrmAppLogin::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	switch (Key)
	{
		case vkReturn:
			btnLogarClick(Sender);
			break;

		case vkEscape:
			ModalResult = mrCancel;
			Close();
			break;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFrmAppLogin::FormClose(TObject *Sender, TCloseAction &Action)
{
	DBModule->Lmr96Connection->Connected = False;
}

//---------------------------------------------------------------------------

void __fastcall TFrmAppLogin::FormCreate(TObject *Sender)
{
	ComboBoxUserName->Clear();

	DBModule->Lmr96Connection->Connected = True;

	DBModule->UserSQLQuery->Open();
	DBModule->UserSQLQuery->First();
	while (!DBModule->UserSQLQuery->Eof)
	{
		ComboBoxUserName->AddItem(DBModule->UserSQLQuery->FieldByName("Column0")->AsString, NULL);
		DBModule->UserSQLQuery->Next();
	}
	DBModule->UserSQLQuery->Close();

	#if ( defined(_DEBUG) && defined(SPEEDY) )
	ComboBoxUserName->ItemIndex = 0;
	ComboBoxUserName->OnChange(this);
	PasswordEdit->Text = "admin";
	#endif
}
//---------------------------------------------------------------------------

