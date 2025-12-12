//---------------------------------------------------------------------------

#ifndef reportmoduleH
#define reportmoduleH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "frxClass.hpp"
//---------------------------------------------------------------------------
class TReportsContainer : public TDataModule
{
__published:	// IDE-managed Components
	TfrxReport *frxReportPlateMap;
	TfrxUserDataSet *frxUserDataSetPlateMap;
	void __fastcall frxUserDataSetPlateMapCheckEOF(TObject *Sender, bool &Eof);
private:	// User declarations
public:		// User declarations
	__fastcall TReportsContainer(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TReportsContainer *ReportsContainer;
//---------------------------------------------------------------------------
#endif
