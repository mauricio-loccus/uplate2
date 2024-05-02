//---------------------------------------------------------------------------

#ifndef STRPLITJOIN_H
#define STRPLITJOIN_H

// functions to split a string by a specific delimiter
#include "unStrUtils.h"

namespace loccus {

// thanks to Evan Teran, http://stackoverflow.com/questions/236129/how-to-split-a-string/236803#236803

// split a string on any character found in the string of delimiters (delims)
ByteArrayList& split(const ByteArray &s, const ByteArray& delims, StlStringList &elems);
ByteArrayList  split(const ByteArray&s, const ByteArray& delims);

// join a vector of elements by a delimiter object.  ostream<< must be defined
// for both class S and T and an ostream, as it is e.g. in the case of strings
// and character arrays
void join(const ByteArrayList& sl, const ByteArray& sep, ByteArray& result);
ByteArray join(const ByteArrayList& sl, const ByteArray& sep);

}
//---------------------------------------------------------------------------
#endif // STRPLITJOIN_H
