//---------------------------------------------------------------------------
#include <algorithm>

#pragma hdrstop

#include "unWellMatrix.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TWellMatrix::TWellMatrix()
{
	Rows = 0;
	Cols = 0;
    mName = "";
}

void __fastcall TWellMatrix::filterWellsByType(TWellType type, WellList& wl)
{
	for (Integer row = 0; row < Rows; row++)
	{
        WellList& wlRef = mMatrixWells[row];
		for (WellList::iterator cIt = wlRef.begin(); cIt != wlRef.end(); cIt++)
		{
			if (cIt->Type == type)
				wl.push_back(*cIt);
		}
	}
}

WellListPointers __fastcall TWellMatrix::filterWellsPointersByType(TWellType type)
{
	WellListPointers wp;

	for (Integer row = 0; row < Rows; row++)
	{
		for (WellList::iterator it = mMatrixWells[row].begin(); it != mMatrixWells[row].end(); it++)
		{
			if (it->Type == type)
				wp.push_back(&(*it));
		}
	}

	return wp;
}

TWell __fastcall TWellMatrix::getMaxWellTypeCount(TWellType type)
{
	WellList wlist;

    filterWellsByType(type, wlist);

	if (wlist.empty())
		return TWell();

	TWell w = *std::max_element(wlist.begin(), wlist.end());

	return w;
}

void __fastcall TWellMatrix::reEnumerateWells(TWellType wt, TCellOptionsData cellOptions)
{
	Integer index = 0;

	if (cellOptions.enumDirection == TEnumerationDir::ndLeftRight)
	{
		for (Integer row = 0; row < Rows; row++)
			for (Integer col = 0; col < Cols; col++)
			{
				TWell& w = mMatrixWells[row][col];
				if (w.Type == wt)
					w.ID = ++index;
			}
	}
	else
	{
		for (Integer col = 0; col < Cols; col++)
			for (Integer row = 0; row < Rows; row++)
			{
				TWell& w = mMatrixWells[row][col];
				if (w.Type == wt)
					w.ID = ++index;
			}
	}
}

WellListPointers::size_type __fastcall TWellMatrix::setAllReplicas(TWell w)
{
	WellListPointers wlp = getAllReplicas(w);

	if (wlp.empty())
		return 0;

	for (WellListPointers::iterator it = wlp.begin(); it != wlp.end(); ++it)
		(*it)->StdValue = w.StdValue;

	return wlp.size();
}

WellListPointers __fastcall TWellMatrix::getAllReplicas(TWell w)
{
	WellListPointers lr;

	for (Integer row = 0; row < Rows; row++)
	{
		for (WellList::iterator it = mMatrixWells[row].begin(); it != mMatrixWells[row].end(); it++)
		{
			if (*it == w)
				lr.push_back(&(*it));
		}
	}

	return lr;
}

