//---------------------------------------------------------------------------

#ifndef unWellMatrixH
#define unWellMatrixH

#include <algorithm>
#include <memory>
#include <vector>
#include <iterator>

#include "unCellOptions.h"
#include "unWell.h"
#include "Singleton.h"

typedef std::vector<TWell> WellList;
typedef std::vector<TWell *> WellListPointers;

class TWellMatrix
{
	public:
		__fastcall TWellMatrix() : Rows(0), Cols(0) {}
		__fastcall TWellMatrix(Integer rows_, Integer cols_) : Rows(rows_), Cols(cols_)
		{
			for (Integer row = 0; row < Rows; row++)
				mMatrixWells.push_back(std::vector<TWell>(Cols, TWell()));
		}

		__fastcall TWellMatrix(const TWellMatrix& rhs)
        {
            Rows = rhs.Rows;
            Cols = rhs.Cols;

            mMatrixWells.clear();
            for (Integer row = 0; row < Rows; ++row)
            {
                WellList wl;

		        std::copy(rhs.mMatrixWells[row].begin(), rhs.mMatrixWells[row].end(), std::back_inserter(wl));

                mMatrixWells.push_back(wl);
            }
        }

        ~TWellMatrix()
        {
            if (!mMatrixWells.empty())
            {
                for (Integer row = 0; row < Rows; ++row)
                    mMatrixWells[row].clear();
            }
        }

		__fastcall void operator =(const TWellMatrix& rhs)
        {
            Rows = rhs.Rows;
            Cols = rhs.Cols;

            mMatrixWells.clear();

            for (Integer row = 0; row < Rows; ++row)
            {
                WellList wl;

		        std::copy(rhs.mMatrixWells[row].begin(), rhs.mMatrixWells[row].end(), std::back_inserter(wl));

                mMatrixWells.push_back(wl);
            }
        }

        WellList& operator[](Integer row)
        {
            return mMatrixWells[row];
        }

        const WellList& operator[](Integer row) const
        {
            return mMatrixWells[row];
        }

		void __fastcall filterWellsByType(TWellType type, WellList& wl);
		WellListPointers __fastcall filterWellsPointersByType(TWellType type);
		TWell __fastcall getMaxWellTypeCount(TWellType type);
		void __fastcall reEnumerateWells(TWellType wt, TCellOptionsData cellOptions);
		WellListPointers::size_type __fastcall setAllReplicas(TWell w);
		WellListPointers __fastcall getAllReplicas(TWell w);

	private:
		Integer Rows, Cols;
		std::vector< std::vector<TWell> > mMatrixWells;
};

typedef std::vector<TWellMatrix> WellMatrixList;
typedef TWellMatrix * TWellMatrixPt;
typedef SingletonPattern<WellMatrixList> TWellMatrixSingleton;
//---------------------------------------------------------------------------
#endif
