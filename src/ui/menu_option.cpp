#include "menu_option.h"

namespace menu
{
	std::istream& operator>>(std::istream& is, menu::option& opt)
	{
		unsigned input;
		is >> input;

		switch (input) {
			case 0:
				opt = menu::option::end;
				break;
			case 1:
				opt = menu::option::add;
				break;
			case 2:
				opt = menu::option::remove;
				break;
			case 3:
				opt = menu::option::change;
				break;
			case 4:
				opt = menu::option::list;
				break;
		}

		if (is.eof()) {
			opt = menu::option::end;
			return is;
		}

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
			case menu::option::change:
				os << "change\n";
				break;
			case menu::option::list:
				os << "list\n";
				break;
		}

		return os;
	}
}
