#include "crcfast.h"

#define WIDTH    (8 * sizeof(crc))
#define TOPBIT   (1 << (WIDTH - 1))

#if (REFLECT_DATA == TRUE)
#undef  REFLECT_DATA
#define REFLECT_DATA(X)			((unsigned char) reflect((X), 8))
#else
#undef  REFLECT_DATA
#define REFLECT_DATA(X)			(X)
#endif

#if (REFLECT_REMAINDER == TRUE)
#undef  REFLECT_REMAINDER
#define REFLECT_REMAINDER(X)	((crc) reflect((X), WIDTH))
#else
#undef  REFLECT_REMAINDER
#define REFLECT_REMAINDER(X)	(X)
#endif

#if REFLECT_REMAINDER == TRUE
static
const uint32_t reflect(const uint32_t data, uint8_t nBits)
{
	uint32_t reflection = 0x00000000;

	for (uint8_t bit = 0; bit < nBits; bit++)
	{
		if (data & 0x01)
			reflection |= (1 << ((nBits-1) - bit));

		data >>= 1;
	}

	return reflection;
}
#endif

crc CRCFast::crcTable[256];

CRCFast::CRCFast()
{
	initTable();
}

uint16_t CRCFast::calculate(const ByteArray& arr)
{
	uint16_t remainder = INITIAL_REMAINDER;
	uint8_t  data = 0;
	ByteArray::size_type size = arr.size();

	for (ByteArray::size_type byte = 0; byte < size; byte++)
	{
		data = REFLECT_DATA(arr[byte]) ^ (remainder >> (WIDTH-8));
		remainder = crcTable[data] ^ (remainder << 8);
	}

	return REFLECT_REMAINDER(remainder) ^ FINAL_XOR_VALUE;
}

void CRCFast::initTable()
{
	uint16_t remainder = 0;

	for (int16_t dividend = 0; dividend < 256; dividend++)
	{
		remainder = dividend << (WIDTH - 8);

		for (uint8_t bit = 8; bit > 0; --bit)
		{
			if (remainder & TOPBIT)
				remainder = (remainder << 1) ^ POLYNOMIAL;
			else
				remainder <<= 1;
		}

		crcTable[dividend] = remainder;
	}
}

