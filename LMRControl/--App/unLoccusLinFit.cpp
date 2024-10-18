//---------------------------------------------------------------------------

#pragma hdrstop

#include "unLoccusLinFit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Double __fastcall LinFitCrossOrigin(const DoubleArray& X,
									const DoubleArray& Y,
									Double& k,
									Double& d,
									Double& fitQual)
{
	d = 0;

	Double sumXY = 0;
	Double sumXSquare = 0;

	for (Integer i = 0; i < X.size(); i++)
	{
		sumXY += (X[i] * Y[i]);
		sumXSquare += std::pow(X[i], 2);
	}

	k = sumXY / sumXSquare;

	DoubleArray oCoeff(1, k);
	DoubleArray adjustedY;

	for (Double i = 0; i < X.size(); i ++)
		adjustedY.push_back(k * X[i] + d);

	Double o2xy = funcO2xy(Y, adjustedY);
	Double avg  = average(Y);
	Double o2y  = funcO2y(Y, avg);

	fitQual = (1.0 - o2xy / o2y);
	return True;
}
