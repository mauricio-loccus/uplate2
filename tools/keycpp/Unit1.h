//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
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
	TGestureListView *lvWindowsList;

	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall TimerTimer(TObject *Sender);
	void __fastcall mExitClick(TObject *Sender);

private:	// User declarations
	void __fastcall Quit();
	void __fastcall UpdateTimer();

public:		// User declarations
	__fastcall TWindowList(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWindowList *WindowList;
//---------------------------------------------------------------------------
#endif
