//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unFrmConfig.h"
#include "unDataModule.h"
#include "unDBModule.h"
#include "unFrmEditUserData.h"
#include "unFrmEditUnities.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFrmAppConfig *FrmAppConfig;
//---------------------------------------------------------------------------
__fastcall TFrmAppConfig::TFrmAppConfig(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmAppConfig::btnCancelClick(TObject *Sender)
{
	mpAppConfig->Load();
	ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TFrmAppConfig::btnApplyClick(TObject *Sender)
{
	mpAppConfig->setDecimalSeparator(teDecimalSeparator->Text[1]);
	mpAppConfig->setThousandSeparator(teThousandSeparator->Text[1]);
	mpAppConfig->setHeadersInCsv(chbHeadersInCsv->Checked);

	if (chbElisaSimulated->Checked && !mpAppConfig->ElisaSimulated)
	{
		TaskMessageDlg(TEXT("Preferências"),
					   TEXT("Atenção, a leitora de ELISA será simulada via software.\n")
					   TEXT("Para que as mudanças sejam efetivadas, reinicie a aplicação."),
					   mtWarning,
					   TMsgDlgButtons() << mbOK, 0);
	}

	mpAppConfig->setSimulatorActive(chbElisaSimulated->Checked);

	if (mpAppConfig->DecimalSeparator == mpAppConfig->ThousandSeparator)
	{
		TaskMessageDlg(TEXT("Preferências"),
					   TEXT("O separadores de decimal e milhar não podem ser iguais. Corrija e tente novamente"),
					   mtError,
					   TMsgDlgButtons() << mbOK, 0);

		return;
	}

	mpAppConfig->Save();
	ModalResult = mrOk;
}
//---------------------------------------------------------------------------


void __fastcall TFrmAppConfig::FormCreate(TObject *Sender)
{
	mpAppConfig = AppConfigSingleton::instance();
}
//---------------------------------------------------------------------------

void __fastcall TFrmAppConfig::FormShow(TObject *Sender)
{
    DBModule->Lmr96Connection->Connected = True;
    DBModule->UserTable->Active = True;
    DBModule->UserClientDataSet->Active = True;

    DBModule->UnidadesTable->Active = True;
	DBModule->UnitiesClientDataSet->Active = True;

	populateUnitiesMap();

    WideChar thSeparator = mpAppConfig->ThousandSeparator;
    WideChar decSeparator = mpAppConfig->DecimalSeparator;

    teDecimalSeparator->Text = decSeparator;
    teThousandSeparator->Text = thSeparator;
	chbHeadersInCsv->Checked = mpAppConfig->HeadersInCsv;
	chbElisaSimulated->Checked = mpAppConfig->ElisaSimulated;

    teDecimalSeparator->SelectAll();
    teDecimalSeparator->SetFocus();

    UserDBGrid->Enabled = mpAppConfig->IsSuperUser;
    UserDBNavigator->Enabled = mpAppConfig->IsSuperUser;

    UnitiesDBGrid->Enabled = mpAppConfig->IsSuperUser;
    UnitiesDBNavigator->Enabled = mpAppConfig->IsSuperUser;
}
//---------------------------------------------------------------------------
void __fastcall TFrmAppConfig::doKeyPressed(System::WideChar& Key)
{
    switch (Key) {
        case VK_ESCAPE:
            btnCancelClick(this);
            break;

        case VK_RETURN:
            btnApplyClick(this);
            break;

        default:
            break;
    }
}

//---------------------------------------------------------------------------

void __fastcall TFrmAppConfig::teThousandSeparatorKeyPress(TObject *Sender, System::WideChar &Key)
{
    doKeyPressed(Key);
}
//---------------------------------------------------------------------------

void __fastcall TFrmAppConfig::teDecimalSeparatorKeyPress(TObject *Sender, System::WideChar &Key)
{
    doKeyPressed(Key);
}
//---------------------------------------------------------------------------

void __fastcall TFrmAppConfig::UserDBNavigatorClick(TObject *Sender, TNavigateBtn Button)
{
    if (TNavigateBtn::nbInsert == Button)
    {
        FrmEditUserData = new TFrmEditUserData(this);
        TModalResult result = FrmEditUserData->ShowModal();

        if (mrCancel == result) {
            FrmEditUserData->Free();
            FrmEditUserData = NULL;

            return;
        }

        DBModule->UserClientDataSet->Append();

        DBModule->UserClientDataSet->FieldByName("LOGIN")->AsString = FrmEditUserData->UserLogin;
        DBModule->UserClientDataSet->FieldByName("PASSWORD")->AsString = FrmEditUserData->UserPassword;
        DBModule->UserClientDataSet->FieldByName("NAME")->AsString = FrmEditUserData->UserName;
        DBModule->UserClientDataSet->FieldByName("SURNAME")->AsString = FrmEditUserData->UserSurname;
		DBModule->UserClientDataSet->FieldByName("DEPT")->AsString = FrmEditUserData->UserDept;
		DBModule->UserClientDataSet->FieldByName("SUPERUSER")->AsInteger = FrmEditUserData->UserIsSuperUser;

		DBModule->UserClientDataSet->Post();
		DBModule->UserClientDataSet->ApplyUpdates(-1);

		FrmEditUserData->Free();
		FrmEditUserData = NULL;

		return;
	}

	if (TNavigateBtn::nbEdit == Button)
	{
		FrmEditUserData = new TFrmEditUserData(this, True);

		FrmEditUserData->UserLogin = DBModule->UserClientDataSet->FieldByName("LOGIN")->AsString;
		FrmEditUserData->UserPassword = DBModule->UserClientDataSet->FieldByName("PASSWORD")->AsString;
		FrmEditUserData->UserName = DBModule->UserClientDataSet->FieldByName("NAME")->AsString;
		FrmEditUserData->UserSurname = DBModule->UserClientDataSet->FieldByName("SURNAME")->AsString;
		FrmEditUserData->UserDept = DBModule->UserClientDataSet->FieldByName("DEPT")->AsString;
		FrmEditUserData->UserIsSuperUser = DBModule->UserClientDataSet->FieldByName("SUPERUSER")->AsInteger;

		TModalResult result = FrmEditUserData->ShowModal();

		if (mrCancel == result) {
			FrmEditUserData->Free();
			FrmEditUserData = NULL;

			return;
		}

		DBModule->UserClientDataSet->FieldByName("LOGIN")->AsString = FrmEditUserData->UserLogin;
		DBModule->UserClientDataSet->FieldByName("PASSWORD")->AsString = FrmEditUserData->UserPassword;
		DBModule->UserClientDataSet->FieldByName("NAME")->AsString = FrmEditUserData->UserName;
		DBModule->UserClientDataSet->FieldByName("SURNAME")->AsString = FrmEditUserData->UserSurname;
		DBModule->UserClientDataSet->FieldByName("DEPT")->AsString = FrmEditUserData->UserDept;
		DBModule->UserClientDataSet->FieldByName("SUPERUSER")->AsInteger = FrmEditUserData->UserIsSuperUser;

		DBModule->UserClientDataSet->Post();
		DBModule->UserClientDataSet->ApplyUpdates(-1);

		FrmEditUserData->Free();
		FrmEditUserData = NULL;

		return;
	}

	if (TNavigateBtn::nbDelete == Button)
	{
		TModalResult response = TaskMessageDlg(TEXT("Confirme a ação"),
											   TEXT("Deseja realmente cancelar o registro desse usuário?"),
											   mtConfirmation,
											   TMsgDlgButtons() << mbNo << mbYes, 0);

		if (mrNo == response)
		{
			DBModule->UserClientDataSet->CancelUpdates();
			return;
		}

		DBModule->UserClientDataSet->ApplyUpdates(-1);
	}
}
//---------------------------------------------------------------------------


void __fastcall TFrmAppConfig::FormClose(TObject *Sender, TCloseAction &Action)
{
	DBModule->Lmr96Connection->Connected = False;
	DBModule->UserTable->Active = False;
	DBModule->UserClientDataSet->Active = False;

	DBModule->UnidadesTable->Active = False;
	DBModule->UnitiesClientDataSet->Active = False;
}
//---------------------------------------------------------------------------

void __fastcall TFrmAppConfig::UnitiesDBNavigatorClick(TObject *Sender, TNavigateBtn Button)
{
	if ((DBModule->UnitiesClientDataSet->RecNo < 6 && TNavigateBtn::nbDelete == Button) ||
		(DBModule->UnitiesClientDataSet->RecNo <= 6 && TNavigateBtn::nbEdit == Button))
	{
		TaskMessageDlg(TEXT("Ação proibida"),
					   TEXT("Não é possível alterar ou cancelar as unidades de medida predefinidas"),
					   mtInformation,
					   TMsgDlgButtons() << mbOK, 0);

		DBModule->UnitiesClientDataSet->CancelUpdates();
		return;
	}

	if (TNavigateBtn::nbInsert == Button)
	{
		FrmEditUnities = new TFrmEditUnities(this);

		TModalResult mr = FrmEditUnities->ShowModal();

		if (mrCancel == mr)
		{
			FrmEditUnities->Free();
			FrmEditUnities = NULL;

			return;
		}

		UnitiesMap::const_iterator cit;
		cit = mUnitiesMap.find(UpperCase(FrmEditUnities->Unity));

		if (cit != mUnitiesMap.end())
		{
			MessageDlg("Unidade de medida já existe, por favor corrija e tente novamente",
					   mtWarning,
					   TMsgDlgButtons() << mbOK, 0);

			FrmEditUnities->Free();
			FrmEditUnities = NULL;

			return;

		}

		DBModule->UnitiesClientDataSet->Append();
		DBModule->UnitiesClientDataSetunidade->Value = FrmEditUnities->Unity;
		DBModule->UnitiesClientDataSetvalor->Value = 0;

		DBModule->UnitiesClientDataSet->Post();
		DBModule->UnitiesClientDataSet->ApplyUpdates(-1);

		FrmEditUnities->Free();
		FrmEditUnities = NULL;

		return;
	}

	if (TNavigateBtn::nbEdit == Button)
	{
		FrmEditUnities = new TFrmEditUnities(this);
		FrmEditUnities->Unity = DBModule->UnitiesClientDataSetunidade->Value;
		FrmEditUnities->Value = DBModule->UnitiesClientDataSetvalor->Value;

		TModalResult mr = FrmEditUnities->ShowModal();

		if (mrCancel == mr)
		{
			FrmEditUnities->Free();
			FrmEditUnities = NULL;

			return;
		}

		DBModule->UnitiesClientDataSetunidade->Value = FrmEditUnities->Unity;
		DBModule->UnitiesClientDataSetvalor->Value = FrmEditUnities->Value;

		DBModule->UnitiesClientDataSet->Post();
		DBModule->UnitiesClientDataSet->ApplyUpdates(-1);

		FrmEditUnities->Free();
		FrmEditUnities = NULL;

		return;
	}

	if (TNavigateBtn::nbDelete == Button)
	{
		TModalResult response = TaskMessageDlg(TEXT("Confirme a ação"),
											   TEXT("Deseja realmente cancelar esta unidade de medida?"),
											   mtConfirmation,
											   TMsgDlgButtons() << mbNo << mbYes, 0);

		if (mrNo == response)
		{
			DBModule->UnitiesClientDataSet->CancelUpdates();
			return;
		}

		DBModule->UnitiesClientDataSet->ApplyUpdates(-1);
	}
}
//---------------------------------------------------------------------------

void __fastcall TFrmAppConfig::populateUnitiesMap()
{
	TSQLQuery *unSQLQuery = new TSQLQuery(this);
	unSQLQuery->SQLConnection = DBModule->Lmr96Connection;

	unSQLQuery->SQL->Add("SELECT * FROM unidades");

	unSQLQuery->Active = True;

	unSQLQuery->First();

	while (!unSQLQuery->Eof)
	{
		String un = unSQLQuery->FieldByName("UNIDADE")->AsString;
		Longint value = unSQLQuery->FieldByName("VALOR")->AsInteger;

		mUnitiesMap[UpperCase(un)] = value;

		unSQLQuery->Next();
	}

	unSQLQuery->Close();

	unSQLQuery->Free();
}


