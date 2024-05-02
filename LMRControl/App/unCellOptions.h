//---------------------------------------------------------------------------

#ifndef unCellOptionsH
#define unCellOptionsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "LMDBaseEdit.hpp"
#include "LMDControl.hpp"
#include "LMDCustomBevelPanel.hpp"
#include "LMDCustomControl.hpp"
#include "LMDCustomEdit.hpp"
#include "LMDCustomExtSpinEdit.hpp"
#include "LMDCustomMaskEdit.hpp"
#include "LMDCustomPanel.hpp"
#include "LMDSpinEdit.hpp"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

enum class TEnumerationDir : Integer
{
	ndTopBottom = 0,
	ndLeftRight = 1
};

struct TCellOptionsData
{
	TEnumerationDir enumDirection;
	Integer replicas;

	TCellOptionsData() : enumDirection(TEnumerationDir::ndTopBottom),
						 replicas(1) {}
};

class TCellOptions : public TForm
{
__published:	// IDE-managed Components
	TRadioGroup *rgEnumDirection;
	TStaticText *StaticText1;
	TLMDSpinEdit *spnReplicas;
	TButton *btnOk;
	TButton *btnCancel;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnOkClick(TObject *Sender);
private:	// User declarations
    TCellOptionsData& mCellOptions;

public:		// User declarations
	__fastcall TCellOptions(TCellOptionsData& data, TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCellOptions *CellOptions;
//---------------------------------------------------------------------------
#endif
