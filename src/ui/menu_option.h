#pragma once

#include <iostream>
#include <array>

namespace menu
{
	enum class opt
	{
		add_card = 'a', remove_card = 'r', change_card = 'c', list_card = 'l', add_cty = 'A', remove_cty = 'R', change_cty = 'C', list_cty = 'L', exit = 'e'
	};

	static constexpr std::array<opt, 9> opts
	{
		opt::add_card, opt::remove_card, opt::change_card, opt::list_card,
			opt::add_cty, opt::remove_cty, opt::change_cty, opt::list_cty, opt::exit
	};

	inline std::istream& operator>>(std::istream& is, opt& op)
	{
		char input;
		is >> input;

		op = static_cast<opt>(input);
		if (std::find(begin(opts), end(opts), op) == opts.end())
			is.setstate(std::ios::failbit);

		return is;
	}

	inline std::ostream& operator<<(std::ostream& os, const opt& opt)
	{
		switch (opt) {
			case opt::add_card:
				return (os << "(a)dd card");
			case opt::remove_card:
				return (os << "(r)emove card");
			case opt::change_card:
				return (os << "(c)hange card");
			case opt::list_card:
				return (os << "(l)ist card");
			case opt::add_cty:
				return (os << "(A)dd category");
			case opt::remove_cty:
				return (os << "(R)emove category");
			case opt::change_cty:
				return (os << "(C)hange category");
			case opt::list_cty:
				return (os << "(L)ist category");
			case opt::exit:
				return (os << "(e)xit");
		}
	}

	inline void print_opts()
	{
		std::cout << "select options: \n";
		for (auto opt : opts)
			std::cout << "  - " << opt << '\n';
	}

}
