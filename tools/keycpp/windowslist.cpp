//---------------------------------------------------------------------------

#include <vcl.h>
#include <PsAPI.hpp>

#pragma hdrstop

#include "windowslist.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TWindowList *WindowList;

//---------------------------------------------------------------------------

__fastcall TWindowList::TWindowList(TComponent* Owner) : TForm(Owner)
{
}

//---------------------------------------------------------------------------

// Callback to collect visible and enabled windows
BOOL __stdcall CALLBACK TWindowList::EnumWindowsToMap(HWND hWnd, LPARAM lParam)
{
	std::map<HWND, UnicodeString>* map;


	map = reinterpret_cast<std::map<HWND, UnicodeString>*>(lParam);
	if (IsWindowVisible(hWnd) && IsWindowEnabled(hWnd))
	{
		TCHAR buffer[256];
		int len = GetWindowText(hWnd, buffer, 256);
		if (len > 0)
			map->insert(std::make_pair(hWnd, UnicodeString(buffer)));
	}

	return TRUE;
}


//----------------------------------------------------------------------------
// Reads the “FileDescription” from the version info of an EXE.
// Falls back to the file name if no description is found.
//----------------------------------------------------------------------------
String __fastcall TWindowList::GetFileDescription(const String &filePath)
{
	DWORD dummy = 0;
	DWORD verSize = GetFileVersionInfoSizeW(
	  filePath.w_str(), &dummy);
	if (verSize == 0)
		return ExtractFileName(filePath);

	BYTE *buffer = new BYTE[verSize];
	if (!GetFileVersionInfoW(
		  filePath.w_str(), 0, verSize, buffer))
	{
		delete[] buffer;
		return ExtractFileName(filePath);
	}

	struct LANGANDCODEPAGE { WORD wLanguage, wCodePage; };
	LANGANDCODEPAGE *lpTranslate = NULL;
	UINT transSize = 0;
	if (!VerQueryValueW(buffer,
		  L"\\VarFileInfo\\Translation",
		  (LPVOID*)&lpTranslate, &transSize) ||
		transSize < sizeof(LANGANDCODEPAGE))
	{
		delete[] buffer;
		return ExtractFileName(filePath);
	}

	wchar_t subBlock[64];
	swprintf(subBlock, 64,
	  L"\\StringFileInfo\\%04x%04x\\FileDescription",
	  lpTranslate->wLanguage,
	  lpTranslate->wCodePage);

	LPWSTR desc = NULL;
	UINT descLen = 0;
	UnicodeString result;

	if (VerQueryValueW(buffer, subBlock,
		  (LPVOID*)&desc, &descLen) && descLen)
		result = desc;
	else
		result = ExtractFileName(filePath);

	delete[] buffer;
	return result;
}

//----------------------------------------------------------------------------
// Given a window handle, returns the friendly app name via version info.
//----------------------------------------------------------------------------
String __fastcall TWindowList::GetProcessName(HWND hWnd)
{
	DWORD pid = 0;
	GetWindowThreadProcessId(hWnd, &pid);
	if (pid == 0)
		return "";

	HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
	if (!hProc)
		return "";

	// retrieve module path
	wchar_t pathBuf[MAX_PATH] = {0};
	if (GetModuleFileNameExW(hProc, NULL, pathBuf, MAX_PATH) == 0)
	{
		CloseHandle(hProc);
		return "";
	}
	CloseHandle(hProc);

	String exePath(pathBuf);

	// Check cache first
	std::map<String, String>::iterator it;
	do
	{
		it = appNameCache.find(exePath);
		if (it != appNameCache.end())
			break;

		String friendlyName = GetFileDescription(exePath);
		appNameCache[exePath] = friendlyName;
	}
	while (true);

	return it->second;
}


//---------------------------------------------------------------------------

// Refresh the internal snapshot and measure elapsed time
void __fastcall TWindowList::RefreshWindows()
{
	DWORD start = GetTickCount();

	// Build new snapshot
	std::map<HWND, String> newMap;
	EnumWindows(EnumWindowsToMap, reinterpret_cast<LPARAM>(&newMap));

	bool changed = false;

	{
	std::map<HWND, String>::iterator it;
	for (it = newMap.begin(); it != newMap.end(); ++it)
	{
		HWND h = it->first;
		if (windowsMap.find(h) == windowsMap.end())
		{
			WindowInfo info;
			info.hWnd      = h;
			info.title     = it->second;
			info.appName   = GetProcessName(h);
			info.timestamp = Now();
			info.present   = true;
			windowsMap[h]  = info;
			changed = true;
		}
	}
	}

	// Detect removals
	std::map<HWND, WindowInfo>::iterator it;
	for (it = windowsMap.begin(); it != windowsMap.end(); ++it)
	{
		HWND h = it->first;
		if (newMap.find(h) == newMap.end() && it->second.present)
		{
			it->second.present   = false;
			it->second.timestamp = Now();
			changed = true;
		}
	}

	// Only rebuild ListView if items added/removed
	if (changed)
	{
		this->UpdateListView();
	}

	DWORD elapsed = GetTickCount() - start;         // Always update the elapsed-time label

	//lblUpdateTime->Caption = "Updated in " + IntToStr(elapsed) + " ms";
}

//---------------------------------------------------------------------------

void __fastcall TWindowList::Quit()
{
	this->Close();
}

//---------------------------------------------------------------------------

void __fastcall TWindowList::UpdateTimer()
{
	Timer->Interval = seInterval->Value * 1000;
	//Timer->Enabled = (Timer->Interval > 0);
}

//---------------------------------------------------------------------------

void __fastcall TWindowList::UpdateListView()
{
	lvWindowsList->Enabled = false;

	lvWindowsList->Items->Clear();

	std::map<HWND, WindowInfo>::iterator it;
	for (it = windowsMap.begin(); it != windowsMap.end(); ++it)
	{
		TListItem *item = lvWindowsList->Items->Add();

		WindowInfo& info = it->second;
		item->Caption = info.title;
		item->SubItems->Add(info.appName);
		item->SubItems->Add(info.timestamp.FormatString("dd/mm/yyyy hh:nn:ss"));
		item->SubItems->Add("0x" + IntToHex((int)info.hWnd, 8));
		//item->Enabled = info.present;
		item->Data = &info;
	}

	lvWindowsList->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TWindowList::FormShow(TObject *Sender)
{
	//TaskDialog->Buttons->Clear();
}

//---------------------------------------------------------------------------

void __fastcall TWindowList::FormCreate(TObject *Sender)
{
	 this->UpdateTimer();
}
//---------------------------------------------------------------------------
void __fastcall TWindowList::TimerTimer(TObject *Sender)
{
	TListItem* liWindow = lvWindowsList->Items->Add();
	liWindow->Caption = "Interval";
}
//---------------------------------------------------------------------------

void __fastcall TWindowList::mExitClick(TObject *Sender)
{
	Quit();
}
//---------------------------------------------------------------------------

void __fastcall TWindowList::seIntervalChange(TObject *Sender)
{
	UpdateTimer();
}
//---------------------------------------------------------------------------

void __fastcall TWindowList::seIntervalEnter(TObject *Sender)
{
	seInterval->SelectAll();
}
//---------------------------------------------------------------------------

void __fastcall TWindowList::bUpdateClick(TObject *Sender)
{
     this->RefreshWindows();
}
//---------------------------------------------------------------------------

void __fastcall TWindowList::lvWindowsListCustomDrawItem(TCustomListView *Sender, TListItem *Item, TCustomDrawState State, bool &DefaultDraw)
{
    WindowInfo *info = reinterpret_cast<WindowInfo*>(Item->Data);
    if (!info->present)
		Sender->Canvas->Font->Color = clGrayText;

    DefaultDraw = true;
}

//---------------------------------------------------------------------------

void __fastcall TWindowList::lvWindowsListCustomDrawSubItem(TCustomListView *Sender, TListItem *Item, int SubItem, TCustomDrawState State, bool &DefaultDraw)
{
	WindowInfo *info = reinterpret_cast<WindowInfo*>(Item->Data);
	if (!info->present)
		Sender->Canvas->Font->Color = clGrayText;

	DefaultDraw = true;
}

//---------------------------------------------------------------------------

void __fastcall TWindowList::lvWindowsListAdvancedCustomDrawItem(TCustomListView *Sender,
          TListItem *Item, TCustomDrawState State, TCustomDrawStage Stage,
          bool &DefaultDraw)
{
if (Stage == cdPrePaint)
    {
        WindowInfo *info = reinterpret_cast<WindowInfo*>(Item->Data);
        if (!info->present)
            Sender->Canvas->Font->Color = clGrayText;
    }
    DefaultDraw = true;  // keep default painting

}
//---------------------------------------------------------------------------

