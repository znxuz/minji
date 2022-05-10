#pragma once

#include <iostream>
#include <array>

namespace menu
{
    enum class practice_opt
    {
	numbered = 'n', time_limited = 't', unlimited = 'u', random = 'r'
    };

    static constexpr std::array<practice_opt, 4> practice_opts
    {
	practice_opt::numbered, practice_opt::time_limited,
	    practice_opt::unlimited, practice_opt::random
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
	    case practice_opt::time_limited:
		return (os << "(t)ime limited");
	    case practice_opt::unlimited:
		return (os << "(u)nlimited");
	    case practice_opt::random:
		return (os << "(r)andom");
	}
    }

}
