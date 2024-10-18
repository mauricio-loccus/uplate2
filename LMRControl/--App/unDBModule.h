//---------------------------------------------------------------------------

#ifndef unDBModuleH
#define unDBModuleH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <Data.DbxSqlite.hpp>
#include <Data.SqlExpr.hpp>
#include <Data.FMTBcd.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
//---------------------------------------------------------------------------
class TDBModule : public TDataModule
{
__published:	// IDE-managed Components
	TSQLConnection *Lmr96Connection;
    TSQLDataSet *UnidadesTable;
    TWideStringField *UnidadesTableunidade;
    TLargeintField *UnidadesTablevalor;
    TDataSetProvider *UnitiesDataSetProvider;
    TClientDataSet *UnitiesClientDataSet;
    TWideStringField *UnitiesClientDataSetunidade;
    TLargeintField *UnitiesClientDataSetvalor;
    TDataSource *UnitiesDataSource;
    TDataSource *UserDataSource;
    TClientDataSet *UserClientDataSet;
    TDataSetProvider *UserDataSetProvider;
    TSQLDataSet *UserTable;
	TWideStringField *UserTablelogin;
	TWideStringField *UserTablepassword;
	TWideStringField *UserTablename;
	TWideStringField *UserTablesurname;
	TWideStringField *UserTabledept;
	TLargeintField *UserTablesuperuser;
	TWideMemoField *UserTablecreation_date;
	TWideMemoField *UserTablealter_date;
	TWideStringField *UserClientDataSetlogin;
	TWideStringField *UserClientDataSetpassword;
	TWideStringField *UserClientDataSetname;
	TWideStringField *UserClientDataSetsurname;
	TWideStringField *UserClientDataSetdept;
	TLargeintField *UserClientDataSetsuperuser;
	TWideMemoField *UserClientDataSetcreation_date;
	TWideMemoField *UserClientDataSetalter_date;
	TSQLQuery *UserQuery;
	TSQLQuery *UserSQLQuery;
	TWideMemoField *UserSQLQueryColumn0;
	void __fastcall DataModuleCreate(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TDBModule(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDBModule *DBModule;
//---------------------------------------------------------------------------
#endif
