//---------------------------------------------------------------------------

#ifndef windowslistH
#define windowslistH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Samples.Spin.hpp>
#include <Vcl.Touch.GestureCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>

#include <map>


// Structure to hold information about each window
struct WindowInfo
{
	HWND      hWnd;       // window handle
	String    title;      // window title
	String    appName;
	TDateTime timestamp;  // time when detected or removed
	bool      present;    // true if still open
};

//---------------------------------------------------------------------------

class TWindowList : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer;
	TMainMenu *MainMenu;
	TMenuItem *Opes1;
	TMenuItem *mExit;
	TPanel *Panel1;
	TButton *bUpdate;
	TSpinEdit *seInterval;
	TLabel *Label1;
	TPanel *pWindowsList;
	TListView *lvWindowsList;

	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall TimerTimer(TObject *Sender);
	void __fastcall mExitClick(TObject *Sender);
	void __fastcall seIntervalChange(TObject *Sender);
	void __fastcall seIntervalEnter(TObject *Sender);
	void __fastcall bUpdateClick(TObject *Sender);
	void __fastcall lvWindowsListCustomDrawItem(TCustomListView *Sender, TListItem *Item,
		  TCustomDrawState State, bool &DefaultDraw);
	void __fastcall lvWindowsListCustomDrawSubItem(TCustomListView *Sender, TListItem *Item,
		  int SubItem, TCustomDrawState State, bool &DefaultDraw);
	void __fastcall lvWindowsListAdvancedCustomDrawItem(TCustomListView *Sender, TListItem *Item,
		  TCustomDrawState State, TCustomDrawStage Stage, bool &DefaultDraw);


private:	// User declarations
	std::map<HWND, WindowInfo> windowsMap;
	std::map<String, String>   appNameCache;  // cache for FileDescription




	static BOOL __stdcall CALLBACK EnumWindowsToMap(HWND hWnd, LPARAM lParam);

	String __fastcall GetFileDescription(const String &filePath);
	String __fastcall TWindowList::GetProcessName(HWND hWnd);

	void __fastcall Quit();
	void __fastcall UpdateTimer();
	void __fastcall UpdateListView();
	void __fastcall RefreshWindows();

public:		// User declarations
	__fastcall TWindowList(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWindowList *WindowList;
//---------------------------------------------------------------------------
#endif
