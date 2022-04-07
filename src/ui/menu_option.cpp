#include "menu_option.h"

namespace menu
{
	std::istream& operator>>(std::istream& is, option& opt)
	{
		int input = 0;
		is >> input;
		opt = static_cast<option>(input);

		return is;
	}

	std::ostream& operator<<(std::ostream& os, const menu::option& opt)
	{
		switch (opt) {
			case menu::option::end:
				os << "end\n";
				break;
			case menu::option::add:
				os << "add\n";
				break;
			case menu::option::remove:
				os << "remove\n";
				break;
			case menu::option::change_card:
				os << "change card\n";
				break;
			case menu::option::change_category:
				os << "change category\n";
				break;
			case menu::option::list:
				os << "list\n";
				break;
		}

		return os;
	}
}
