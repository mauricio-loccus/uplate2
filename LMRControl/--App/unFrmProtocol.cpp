//---------------------------------------------------------------------------

#include <vcl.h>

#include <memory>

#pragma hdrstop

#include "unFrmProtocol.h"
#include "unDBModule.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmProtocol *FrmProtocol;
//---------------------------------------------------------------------------
__fastcall TFrmProtocol::TFrmProtocol(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmProtocol::FormCreate(TObject *Sender)
{
//	DBModule->ProtocolDataSet->Open();
//
//	while (!DBModule->ProtocolDataSet->Eof)
//	{
//		String ProtocolName = DBModule->ProtocolDataSetNAME->Value;
//		cbProtocolName->Items->Add(ProtocolName);
//		DBModule->ProtocolDataSet->Next();
//	}
//
//	DBModule->ProtocolDataSet->Close();
}
//---------------------------------------------------------------------------

System::Largeint __fastcall TFrmProtocol::SaveNew(System::Largeint userID)
{
//	try
//	{
//		std::unique_ptr<TSQLDataSet> query(new TSQLDataSet(this));
//		query->SQLConnection = DBModule->DBConnection;
//		query->CommandText = "SELECT MAX(ID) FROM PROTOCOL";
//
//		std::unique_ptr<TDataSetProvider> dsProvider(new TDataSetProvider(this));
//		dsProvider->Name = "QueryProvider";
//		dsProvider->DataSet = query.get();
//
//		std::unique_ptr<TClientDataSet> cdsClientDataSet(new TClientDataSet(this));
//		cdsClientDataSet->ProviderName = dsProvider->Name;
//
//		cdsClientDataSet->Open();
//
//		System::Largeint newProtocolID = 0;
//
//		if (!cdsClientDataSet->FieldByName("Column0")->IsNull)
//			newProtocolID = cdsClientDataSet->FieldByName("Column0")->AsInteger;
//
//		cdsClientDataSet->Close();
//
//		DBModule->ProtocolClientDataSet->Open();
//
//		DBModule->ProtocolClientDataSet->Append();
//
//		DBModule->ProtocolClientDataSet->FieldByName("ID")->AsInteger = newProtocolID+1;
//		DBModule->ProtocolClientDataSet->FieldByName("USERID")->AsInteger = userID;
//		DBModule->ProtocolClientDataSet->FieldByName("NAME")->AsString = cbProtocolName->Text.Trim();
//		DBModule->ProtocolClientDataSet->FieldByName("DESCR")->AsString = MemoProtocolDescription->Lines->Text.Trim();
//		DBModule->ProtocolClientDataSet->FieldByName("CREATIONDATE")->AsString = FormatDateTime("yyyy-mm-dd", Now());
//
//		DBModule->ProtocolClientDataSet->Post();
//		DBModule->ProtocolClientDataSet->ApplyUpdates(-1);
//
//		DBModule->ProtocolDataSet->Close();
//
//		return newProtocolID;
//	}
//	catch (const Exception& e)
//	{
//		MessageDlg(e.Message, mtWarning, TMsgDlgButtons() << mbOK, 0);
//	}

	return -1;
}

void __fastcall TFrmProtocol::UpdateRecord(System::Largeint userID, System::Largeint protocolID)
{
//	try
//	{
//		DBModule->ProtocolClientDataSet->Open();
//
//		DBModule->ProtocolClientDataSet->Filter = Format("ID = %d", ARRAYOFCONST((protocolID)));
//		DBModule->ProtocolClientDataSet->Filtered = True;
//
//		DBModule->ProtocolClientDataSet->FieldByName("USERID")->AsLargeInt = userID;
//		DBModule->ProtocolClientDataSet->FieldByName("NAME")->AsString = cbProtocolName->Text;
//		DBModule->ProtocolClientDataSet->FieldByName("DESCR")->AsString = MemoProtocolDescription->Lines->Text;
//		DBModule->ProtocolClientDataSet->FieldByName("CREATIONDATE")->AsDateTime = Now();
//
//		DBModule->ProtocolClientDataSet->Post();
//		DBModule->ProtocolClientDataSet->ApplyUpdates(-1);
//
//		DBModule->ProtocolClientDataSet->Close();
//	}
//	catch (const Exception& e)
//	{
//		MessageDlg(e.Message, mtWarning, TMsgDlgButtons() << mbOK, 0);
//		return;
//	}
}


