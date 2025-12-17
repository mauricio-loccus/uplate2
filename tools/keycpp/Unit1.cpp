//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TWindowList *WindowList;

//---------------------------------------------------------------------------

__fastcall TWindowList::TWindowList(TComponent* Owner) : TForm(Owner)
{
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
	Timer->Enabled = (Timer->Interval > 0);
}

//---------------------------------------------------------------------------

void __fastcall TWindowList::FormShow(TObject *Sender)
{
	//TaskDialog->Buttons->Clear();
}

//---------------------------------------------------------------------------

void __fastcall TWindowList::FormCreate(TObject *Sender)
{
	 Timer->Interval = seInterval->Value * 1000;
	 Timer->Enabled = True;
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

