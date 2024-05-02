//---------------------------------------------------------------------------
#include <memory>

#include <boost/algorithm/string.hpp>

#pragma hdrstop

#include "unStrSplitJoin.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace loccus {
ByteArrayList& split(const ByteArray& s, const ByteArray& delims, ByteArrayList& elems)
{
	boost::split(elems, s, boost::is_any_of(delims));

	return elems;
}

ByteArrayList split(const ByteArray& s, const ByteArray& delims)
{
	ByteArrayList elems;
	return split(s, delims, elems);
}

void join(const ByteArrayList& sl, const ByteArray& sep, ByteArray& result)
{
	result = boost::join(sl, sep);
}

ByteArray join(const ByteArrayList& sl, const ByteArray& sep)
{
	ByteArray joined;

	join(sl, sep, joined);

	return joined;
}
}
