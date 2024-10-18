//---------------------------------------------------------------------------

#ifndef unFrmSimulatedValuesH
#define unFrmSimulatedValuesH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "LMDGrid.hpp"
#include "SDL_statis.hpp"
#include <Vcl.Grids.hpp>

#include "unConfig.h"
#include "unElisaDevice.h"
#include "LMDCustomComponent.hpp"
#include "LMDVistaDialogs.hpp"
#include <Vcl.Mask.hpp>

//---------------------------------------------------------------------------
class TFrmSimulatedValues : public TForm
{
__published:	// IDE-managed Components
	TButton *btnRandom;
	TRandGen *RandGen;
	TButton *btnClearValues;
	TButton *btnClose;
    TButton *btnLoadCSV;
	TStringGrid *RawValuesGrid;
	void __fastcall btnRandomClick(TObject *Sender);
	void __fastcall btnClearValuesClick(TObject *Sender);
    void __fastcall btnLoadCSVClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
	void __fastcall btnCloseClick(TObject *Sender);
	void __fastcall RawValuesGridSetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
	void __fastcall RawValuesGridEnter(TObject *Sender);
	void __fastcall RawValuesGridExit(TObject *Sender);
	void __fastcall RawValuesGridSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall RawValuesGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);
	void __fastcall RawValuesGridGetEditText(TObject *Sender, int ACol, int ARow, UnicodeString &Value);



private:	// User declarations
	RawDataMatrix& rawData;
	PAppConfig m_appConfig;

	Integer m_editingCol, m_editingRow;

public:		// User declarations
	__fastcall TFrmSimulatedValues(RawDataMatrix& data, TComponent* Owner = NULL);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmSimulatedValues *FrmSimulatedValues;
//---------------------------------------------------------------------------
#endif
