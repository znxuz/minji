#pragma once

#include <algorithm>
#include <iostream>
#include <array>

namespace practice
{
    enum class practice_opt
    {
	numbered = 'n', unlimited = 'u', single_random = 's', exit = 'e'
	     // , time_limited = 't'
    };

    static constexpr std::array<practice_opt, 4> practice_opts
    {
	practice_opt::numbered, practice_opt::unlimited, practice_opt::single_random, practice_opt::exit
    };

    inline std::istream& operator>>(std::istream& is, practice_opt& opt)
    {
	char in;
	is >> in;

	opt = static_cast<practice_opt>(in);
	if (std::find(begin(practice_opts), end(practice_opts), opt) ==
		end(practice_opts))
	    is.setstate(std::ios::failbit);

	return is;
    }

    inline std::ostream& operator<<(std::ostream& os, const practice_opt& opt)
    {
	switch (opt) {
	    case practice_opt::numbered:
		return (os << "(n)umbered");
	    case practice_opt::unlimited:
		return (os << "(u)nlimited");
	    case practice_opt::single_random:
		return (os << "(s)ingle random");
	    case practice_opt::exit:
		return (os << "(e)xit");
	}
	return os;
    }

}
