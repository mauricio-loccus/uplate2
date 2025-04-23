//---------------------------------------------------------------------------

#ifndef WellH
#define WellH

#include <System.hpp>

enum class TWellType : Integer
{
	wlEmpty  = 0,
	wlBlank  = 4,
	wlNegativeControl = 8,
	wlPositiveControl = 12,
	wlQualityControl = 16,
	wlConcentrationStd = 20,
	wlUnknown = 24
};

class TWell
{
	public:
		__fastcall TWell() : mPlateNum(0), mRow(0), mCol(0), mType(TWellType::wlEmpty),
							 mId(0), mLabel(""), mStdValue(0), mRawValue(0), mRawBlankReducedValue(0),
							 mConcentration(0), mStdDeviation(0), mCoefVariation(0),
                             mMinValRepl(0), mMaxValRepl(0) {}

		__fastcall TWell(const TWell& well)
		{
			mPlateNum = well.mPlateNum;
			mRow = well.mRow;
			mCol = well.mCol;
			mType = well.mType;
			mId = well.mId;
			mLabel = well.mLabel;
			mStdValue = well.mStdValue;
			mRawValue = well.mRawValue;
			mRawBlankReducedValue = well.mRawBlankReducedValue;
			mConcentration = well.mConcentration;
            mStdDeviation = well.mStdDeviation;
            mCoefVariation = well.mCoefVariation;
            mMinValRepl = well.mMinValRepl;
            mMaxValRepl = well.mMaxValRepl;
		}

		__fastcall ~TWell() {}

		inline __fastcall Boolean operator <(const TWell& w)
		{
			if (mPlateNum < w.mPlateNum)
				return True;

			if (mId < w.mId)
				return True;

			return False;
		}

		inline __fastcall Boolean operator <(const TWell *w)
		{
			return (*this) < (*w);
		}

		inline __fastcall Boolean operator >(const TWell& w)
		{
			if (mPlateNum > w.mPlateNum)
				return True;

			if (mId > w.mId)
				return True;

			return False;
		}

		inline __fastcall Boolean operator >(const TWell *w)
		{
			return (*this) > (*w);









		}

		inline __fastcall Boolean operator ==(const TWell& w)
		{
			return (mPlateNum == w.mPlateNum && mType == w.mType && mId == w.mId);
		}

		inline __fastcall Boolean operator !=(const TWell& w)
		{
			return (mPlateNum != w.mPlateNum || mType != w.mType || mId != w.mId);
		}

		__property Integer PlateNumber = {read=mPlateNum, write=mPlateNum};
		__property TWellType Type = {read=mType, write=mType};
		__property Integer Row = {read=mRow, write=mRow};
		__property Integer Col = {read=mCol, write=mCol};
		__property Integer ID = {read=mId, write=mId};
		__property String Label = {read=mLabel, write=mLabel};
		__property Double StdValue = {read=mStdValue, write=mStdValue};
		__property Double RawValue = {read=mRawValue, write=mRawValue};
		__property Double RawValueFilter2 = {read=mRawValueFilter2, write=mRawValueFilter2};
		__property Double RawBlankReducedValue = {read=mRawBlankReducedValue, write=mRawBlankReducedValue};
		__property Double ConcentrationValue = {read=mConcentration, write=mConcentration};
		__property String Interpret = {read=mInterpret, write=mInterpret};
		__property TTime  Timestamp = {read=mTimestamp, write=mTimestamp};
        __property Double StdDeviation = {read=mStdDeviation, write=mStdDeviation};
        __property Double CoefVariation = {read=mCoefVariation, write=mCoefVariation};
        __property Double MinimumValue = {read=mMinValRepl, write=mMinValRepl};
        __property Double MaximumValue = {read=mMaxValRepl, write=mMaxValRepl};

		String __fastcall typeToString();

	private:                                       //Adicionar Subject ID e Sample ID
		// Plate ID - Identificação do plate
		Integer   mPlateNum;

		// Mapeamento da posição do well dentro da matriz
		Integer   mRow, mCol;

		// Identifica o tipo de well
		TWellType mType;

		// Número do tipo do well (ex.: tipo: blank1, blank2... blankN
		Integer   mId;

		// Rótulo do well
		String    mLabel;

		// Valor Raw obtido da leitura
		Double    mRawValue;

		// Valor Raw obtido da leitura - usanndo Filter2
		Double    mRawValueFilter2;

		// Valor Raw obtido da leitura deduzido da média dos Brancos se houver.
		// Na ausência, recebe o mesmo valor de RAW
		Double    mRawBlankReducedValue;

		// Valor padrão do tipo (ex.: Padrão de concentração, Padrão de QC, etc...
		Double	  mStdValue;

		// Valor da Concentração após cálculo, utilizando como entrada o valor de
		// mRawBlankReducedValue
		Double    mConcentration;

		// String de interpretação
		String    mInterpret;

		// Timestamp para uso futuro.
		TTime     mTimestamp;

        // Desvio padrão, valorizado em caso de réplicas
        Double    mStdDeviation;

        // Coeficiente de variação
        Double    mCoefVariation;

        // Valore mínimo e máximo para réplicas
        Double    mMinValRepl;
        Double    mMaxValRepl;
};

 //---------------------------------------------------------------------------
#endif
