//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unFrmAbout.h"
#include "unDataModule.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LMDBaseControl"
#pragma link "LMDBaseGraphicButton"
#pragma link "LMDBaseGraphicControl"
#pragma link "LMDCustomMMButton"
#pragma link "LMDMMButton"
#pragma resource "*.dfm"
TFrmAbout *FrmAbout;
//---------------------------------------------------------------------------
__fastcall TFrmAbout::TFrmAbout(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmAbout::spdButtonLoccusClick(TObject *Sender)
{
	Screen->Cursor = crHourGlass;
	ShellExecute(Handle, TEXT("open"), TEXT("http://www.loccus.com.br"),
				 NULL,NULL,SW_SHOWNORMAL);
	Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------
void __fastcall TFrmAbout::FormShow(TObject *Sender)
{
	const String InfoStr[10] = {TEXT("CompanyName"),
								TEXT("FileDescription"),
								TEXT("FileVersion"),
								TEXT("InternalName"),
								TEXT("LegalCopyright"),
								TEXT("LegalTradeMarks"),
								TEXT("OriginalFileName"),
								TEXT("ProductName"),
								TEXT("ProductVersion"),
								TEXT("Comments")
	};

	DWORD dwReserved = 0L;
	String ExeName = Application->ExeName;
	DWORD dwSize = GetFileVersionInfoSize(ExeName.c_str(), (LPDWORD)&dwReserved);
	if (0 >=dwSize )
	{
		MessageDlg(String(TEXT("No version info!")),
				   mtInformation,
				   TMsgDlgButtons() << mbOK,
				   0);

		return;
	}

	String temp = TEXT("VersionInfoSize = ") + IntToStr((INT32)dwSize);

	LPTSTR verInfoBuffer = new TCHAR[dwSize+1];

	GetFileVersionInfo(ExeName.c_str(), 0, dwSize, verInfoBuffer);

	UINT len = 0;
	VS_FIXEDFILEINFO *lpffi = NULL;

	VerQueryValue(verInfoBuffer, TEXT("\\"), &(LPVOID)lpffi, &len);

	struct {
		WORD language;
		WORD characterSet;
	} *lpTranslation;

	VerQueryValue(verInfoBuffer,
				  TEXT("\\VarFileInfo\\Translation"),
				  (LPVOID *)&lpTranslation,
				  &len);

	String queryKey = TEXT("\\StringFileInfo\\") +
					  IntToHex(lpTranslation[0].language, 4) +
					  IntToHex(lpTranslation[0].characterSet, 4) +
					  TEXT("\\");

	LPTSTR pValue = NULL;
	UINT wLen = 0;

	String st;

	st = queryKey + TEXT("ProductName");

	if (VerQueryValue(verInfoBuffer, st.c_str(), (LPVOID *)&pValue, &wLen))
		lbProdName->Caption = String("Sofware: ") + pValue;

	st = queryKey + TEXT("FileVersion");

	if (VerQueryValue(verInfoBuffer, st.c_str(), (LPVOID *)&pValue, &wLen))
		lbBuildVersion->Caption = String("Build: ") + pValue;

	st = queryKey + TEXT("LegalCopyright");

	if (VerQueryValue(verInfoBuffer, st.c_str(), (LPVOID *)&pValue, &wLen))
		lbCopyright->Caption = pValue;

	delete verInfoBuffer;
}
//---------------------------------------------------------------------------
void __fastcall TFrmAbout::FormKeyPress(TObject *Sender, System::WideChar &Key)
{
	switch (Key)
	{
		case VK_ESCAPE:
		case VK_RETURN:
			ModalResult = mrClose;
			break;

		default:
			break;
	}
}
//---------------------------------------------------------------------------


