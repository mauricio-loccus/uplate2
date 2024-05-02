#ifndef MEMSTREAM_H
#define MEMSTREAM_H

#include <cstdint>
#include <cstring>
#include <vector>
#include <streambuf>
#include <iostream>
#include <memory>

template<std::size_t N>
class memstreambuf : public std::streambuf
{
	std::vector<char> buf_(N);

	public:
	memstreambuf()
	{
		setbuf(buf_.data(), buf_.size());
	}

	inline virtual std::streambuf * setbuf(traits_type::char_type *s, std::streamsize n)
		//virtual std::streambuf *setbuf(char_type * const s, std::streamsize const n)
	{
		auto const begin(s);
		auto const end(s + n);

		setg(begin, begin, end);
		setp(begin, end);

		return this;
	}

	pos_type seekpos(pos_type const pos,
		std::ios_base::open_mode const wich = std::ios_base::in |
		std::ios_base::out)
	{
		switch (wich)
		{
			case std::ios_base::in:
				if (pos < egptr() - eback())
				{
					setg(eback(), eback() + pos, egptr());

					return pos;
				}

				break;

			case std::ios_base::out:
				if (pos < epptr() - pbase())
				{
					setp(pbase(), epptr());
					pbump(pos);

					return pos;
				}

				break;
		}

		return pos_type(off_type(-1));
	}

	inline virtual std::streamsize xsgetn(char_type *s, std::streamsize count)
	{
        std::streamsize size(min(egptr() - gptr(), count));

        if (egptr() == gptr())
            return traits_type::eof();

        std::memcpy(s, gptr(), static_cast<std::size_t>(size));

        gbump(static_cast<int>(size));

        return size;
    }

    inline virtual std::streamsize xsputn(char_type *s, std::streamsize count)
    {
        std::streamsize size(min(epptr() - pptr(), count));

        if (epptr() == pptr())
            return traits_type::eof();

        std::memcpy(pptr(), s, static_cast<std::size_t>(size));

        pbump(static_cast<int>(size));

        return size;
    }
};

template <std::size_t N = 1024>
class memstream : public memstreambuf<N>,
	public std::istream,
	public std::ostream
{
	public:
		memstream() : std::istream(this), std::ostream(this) {}
};

#endif // MEMSTREAM_H

