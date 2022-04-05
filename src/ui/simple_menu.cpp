#include "simple_menu.h"
#include <ios>
#include <limits>

namespace
{
	menu::option parse_input()
	{
		menu::option opt;
		do {
			std::cin >> opt;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		} while (std::cin.fail() && !std::cin.eof());

		return opt;
	}

	void print_menu()
	{
		std::cout << "options\n"
			"(0) end\n"
			"(1) add\n"
			"(2) remove\n"
			"(3) change\n"
			"(4) list\n"
			"\n"
			"choose: ";
	}

	void exec_opt(const menu::option& opt)
	{
		// TODO
	}
}

void simple_menu()
{

	menu::option opt;
	do {
		print_menu();
		opt = parse_input();
		exec_opt(opt);
	} while (opt != menu::option::end);
}
