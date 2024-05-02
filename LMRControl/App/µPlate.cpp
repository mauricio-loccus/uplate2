//---------------------------------------------------------------------------

#include <vcl.h>
#include <tchar.h>
#pragma hdrstop

//---------------------------------------------------------------------------
USEFORM("unFrmWait.cpp", FrmWait);
USEFORM("unfrmSplash.cpp", FrmSplash);
USEFORM("unInputFloatValue.cpp", InputFloatValue);
USEFORM("unFrmKineticStatus.cpp", FrmKineticStatus);
USEFORM("unFrmFiltersEdit.cpp", FrmFiltersEdit);
USEFORM("unFrmMain.cpp", MainForm);
USEFORM("unFrmSimulatedValues.cpp", FrmSimulatedValues);
USEFORM("unFrmProtocol.cpp", FrmProtocol);
USEFORM("unWellResult.cpp", WellResult); /* TFrame: File Type */
USEFORM("unWellsEdit.cpp", WellsEdit); /* TFrame: File Type */
USEFORM("unRenamePlate.cpp", FrmRenamePlate);
USEFORM("unFrmEditUserData.cpp", FrmEditUserData);
USEFORM("unCellOptions.cpp", CellOptions);
USEFORM("unFrmAbout.cpp", FrmAbout);
USEFORM("unFrmAppLogin.cpp", FrmAppLogin);
USEFORM("unFrmEditUnities.cpp", FrmEditUnities);
USEFORM("unFrmConfig.cpp", FrmAppConfig);
USEFORM("unDataModule.cpp", MyDataModule); /* TDataModule: File Type */
USEFORM("unDBModule.cpp", DBModule); /* TDataModule: File Type */
//---------------------------------------------------------------------------
#include "unFrmSplash.h"
#include "unFrmMain.h"

//---------------------------------------------------------------------------

int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	if (TMainForm::AlreadyRunning())
	{
		Application->MessageBox(TEXT("Já existe uma instância da aplicação ativa.\n")
								TEXT("Por favor fechar a instância anterior e tentar novamente."),
								TEXT("Loccus Biotecnologia"), MB_OK);

		return EXIT_FAILURE;
	}

	try
	{
		Application->Initialize();

		Application->MainFormOnTaskBar = true;
		Application->Title = TEXT("µPlate");

		Application->CreateForm(__classid(TMyDataModule), &MyDataModule);
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TFrmSplash), &FrmSplash);
		Application->CreateForm(__classid(TDBModule), &DBModule);
		FormatSettings.ShortDateFormat = TEXT("dd/mm/yyyy");
		FormatSettings.LongDateFormat  = TEXT("dddddd, d de mmmm de yyyy");
		FormatSettings.ShortTimeFormat = TEXT("hh:nn:ss");
		FormatSettings.LongTimeFormat  = TEXT("h hora(s), nn minuto(s) e ss segundo(s)");
		FormatSettings.DateSeparator   = '/';
		FormatSettings.TimeSeparator   = ':';
		FormatSettings.ThousandSeparator = ',';
		FormatSettings.DecimalSeparator = '.';

		FrmSplash->Show();

		Application->Run();
    }
    catch (Exception &exception)
    {
		 Application->ShowException(&exception);
    }
    catch (...)
    {
         try
         {
             throw Exception("");
         }
         catch (Exception &exception)
         {
             Application->ShowException(&exception);
         }
    }
    return 0;
}

