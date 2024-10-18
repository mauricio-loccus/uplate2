#ifndef STRUTILS_H
#define STRUTILS_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#if defined(_UNICODE)
typedef std::wstring StlString;
typedef std::vector<StlString> StlStringList;
typedef std::wstringstream StlStringStream;
typedef std::wistringstream IStlStringStream;
typedef std::wostringstream OStlStringStream;
#else
typedef std::string StlString;
typedef std::vector<StlString> StlStringList;
typedef std::stringstream StlStringStream;
typedef std::istringstream IStlStringStream;
typedef std::ostringstream OStlStringStream;
#endif

typedef std::string ByteArray;
typedef std::vector<ByteArray> ByteArrayList;
typedef std::istringstream IByteArrayStream;
typedef std::ostringstream OByteArrayStream;

namespace loccus
{
	inline template<typename Type>
	const StlString ToString(Type value)
	{
		OStlStringStream os;

		os << value;

		return os.str();
	}

	inline template<typename Type>
	const StlString ToString(Type value, std::ios_base& (*fmt)(std::ios_base&))
	{
		OStlStringStream os;

		os << fmt << value;

		if (os.bad())
			return StlString();

		return os.str();
	}

	inline template<typename Type>
	bool ToString(Type value, StlString& s, std::ios_base& (*fmt)(std::ios_base&) = std::dec)
	{
		OStlStringStream os(s);

		os << fmt << value;

		return !os.fail();
	}

	inline template<typename Type>
	const ByteArray ToByteArray(Type value)
	{
		OByteArrayStream os;

		os << value;

		return os.str();
	}

	inline template<typename Type>
	const ByteArray ToByteArray(Type value, std::ios_base& (*fmt)(std::ios_base&))
	{
		OByteArrayStream os;

		os << fmt << value;

		if (os.bad())
			return ByteArray();

		return os.str();
	}

	inline template<typename Type>
	bool ToByteArray(Type value, ByteArray& s, std::ios_base& (*fmt)(std::ios_base&) = std::dec)
	{
		OByteArrayStream os(s);

		os << fmt << value;

		return !os.fail();
	}

	inline template<typename Type>
	const Type FromString(const ByteArray& s)
	{
		Type v;

		IStlStringStream is(s);

		is >> v;

		return v;
	}

	inline template<typename Type>
	const Type FromString(const StlString& s, std::ios_base& (*fmt)(std::ios_base&))
	{
		Type v;

		IStlStringStream is(s);

		is >> fmt >> v;

		return v;
	}

	inline template<typename Type>
	bool FromString(Type& v, const StlString& s, std::ios_base& (*fmt)(std::ios_base&) = std::dec)
	{
		IStlStringStream is(s);

		is >> fmt >> v;

		return !is.fail();
	}

	inline template<typename Type>
	const Type FromByteArray(const ByteArray& s)
	{
		Type v;

		IByteArrayStream is(s);

		is >> v;

		return v;
	}

	inline template<typename Type>
	const Type FromByteArray(const ByteArray& s, std::ios_base& (*fmt)(std::ios_base&))
	{
		Type v;

		IByteArrayStream is(s);

		is >> fmt >> v;

		return v;
	}

	inline template<typename Type>
	bool FromByteArray(Type& v, const ByteArray& s, std::ios_base& (*fmt)(std::ios_base&) = std::dec)
	{
		IByteArrayStream is(s);

		is >> fmt >> v;

		return !is.fail();
	}

	inline bool endsWith(const ByteArray& s, const ByteArray& suffix)
	{
		return s.size() >= suffix.size() &&
			   s.substr(s.size() - suffix.size()) == suffix;
	}

	inline bool startsWith(const ByteArray& s, const ByteArray& prefix)
	{
		return s.size() > prefix.size() &&
			   s.substr(0, prefix.size()) == prefix;
	}
}
#endif

