#pragma once

#include <iostream>

namespace menu
{
	enum class option
	{
		print_menu = 0, add, remove, change_card, change_category, remove_category, list, end
	};

	inline std::istream& operator>>(std::istream& is, menu::option& opt)
	{
		int input = 0;
		is >> input;
		opt = static_cast<option>(input);

		return is;
	}

	inline void print_menu()
	{
		std::cout << "options for category " << "\n"
			"  (1) add\n"
			"  (2) remove\n"
			"  (3) edit\n"
			"  (4) change category\n"
			"  (5) remove category\n"
			"  (6) list\n"
			"  (7) end\n"
			"\n"
			"  >> ";
	}

}
