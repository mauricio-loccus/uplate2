//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unfrmSplash.h"
#include "unFrmMain.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmSplash *FrmSplash;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TFrmSplash::FormCreate(TObject *Sender)
{
	Image->Align = alClient;
}
//---------------------------------------------------------------------------

void __fastcall TFrmSplash::CloseTimerTimer(TObject *Sender)
{
    this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFrmSplash::FormClose(TObject *Sender, TCloseAction &Action)
{
    this->CloseTimer->Enabled = false;
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TFrmSplash::FormDestroy(TObject *Sender)
{
	TMainForm* owner = dynamic_cast<TMainForm*>(Owner);
	if (owner != NULL)
	{
		owner->LoginRequest();
	}
}
//---------------------------------------------------------------------------
