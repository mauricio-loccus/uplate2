//---------------------------------------------------------------------------

#ifndef unLoccusLinFitH
#define unLoccusLinFitH

#include <system.hpp>

#include <math.h>
#include <vector>

typedef std::vector<Double> DoubleArray;

template<typename T>
T funcO2xy(const std::vector<T>& oY, const std::vector<T>& iY)
{
	T nTotY = 0;

	for (size_t i = 0; i < oY.size(); ++i)
		nTotY += std::pow(oY[i] - iY[i], 2);

	return nTotY / oY.size();
}

template<typename T>
T average(const std::vector<T>& v)
{
	T sum = 0;

	for (size_t i = 0; i < v.size(); ++i)
		sum += v[i];

	return sum / v.size();
}

template<typename T>
T funcO2y(const std::vector<T>& y, const T avg)
{
	T sum = 0;

	for (size_t i = 0; i < y.size(); ++i)
		sum += std::pow(y[i] - avg, 2);

	return sum / y.size();
}

Double __fastcall LinFitCrossOrigin(const DoubleArray& X,
									const DoubleArray& Y,
									Double& k,
									Double& d,
									Double& fitQual);
//---------------------------------------------------------------------------
#endif
