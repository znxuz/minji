#include <compare>
#include <ios>
#include <limits>
#include <memory>

#include "simple_menu.h"
#include "../minji/category.h"
#include "menu_option.h"

namespace
{
	std::weak_ptr<minji::category> choose_category(std::vector<std::shared_ptr<minji::category>>& categories)
	{
		std::weak_ptr<minji::category> chosen;
		bool make_new = categories.empty();

		if (!make_new) {
			std::cout << "choose a category:\n";
			do {
				std::cout << "  (0) create a new category\n";
				for (size_t i = 0; i < categories.size(); ++i)
					std::cout << "  (" << (i + 1) << ") " << categories[i]->name() << '\n';
				std::cout << "  >> ";
				size_t choice = 0;
				std::cin.clear();
				std::cin >> choice;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				if ((choice == 0 && std::cin.fail()) || choice > categories.size())
					std::cerr << "invalid input, try again\n";
				else if (choice == 0)
					make_new = true;
				else
					chosen = categories[choice - 1];
			} while (!std::cin.eof() && std::cin.fail());
		}

		if (make_new && !std::cin.fail()) {
			std::cout << "create a category:\n";
			std::string name;
			do {
				std::cout << "  enter a name >> ";
				std::getline(std::cin, name);
			} while (!std::cin.eof() && std::cin.fail());

			if (std::cin.eof())
				return std::weak_ptr<minji::category>();

			categories.emplace_back(std::make_shared<minji::category>(name));
			return categories.back();
		}

		return chosen;
	}

	void remove_category(std::vector<std::shared_ptr<minji::category>>& categories)
	{
		// TODO
	}

	menu::option parse_input(menu::option prev_opt)
	{
		if (prev_opt != menu::option::print_menu)
			return menu::option::print_menu;

		menu::option opt = menu::option::end;
		while (!(std::cin >> opt) && !std::cin.eof()) {
			std::cerr << "  invalid option, try again\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			menu::print_menu();
		}

		if (std::cin.eof())
			return menu::option::end;
		return opt;
	}

	void exec_opt(menu::option opt, std::weak_ptr<minji::category>& cty,
			std::vector<std::shared_ptr<minji::category>>& categories)
	{
		switch (opt) {
			case menu::option::print_menu:
				menu::print_menu();
				break;
			case menu::option::change_category:
				cty = choose_category(categories);
				break;
			case menu::option::remove_category:
				remove_category(categories);
		}
		// TODO
	}
}

void simple_menu(std::vector<std::shared_ptr<minji::category>> categories)
{
	std::weak_ptr<minji::category> cty;
	menu::option opt = menu::option::change_category;
	do {
		std::cout << '\n';
		exec_opt(opt, cty, categories);
		if (cty.lock())
			opt = parse_input(opt);
		else
			opt = menu::option::end;
	} while (opt != menu::option::end);
}
