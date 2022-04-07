#include <ios>
#include <limits>
#include <memory>

#include "simple_menu.h"
#include "menu_option.h"
#include "../minji/category.h"

namespace
{
	std::weak_ptr<minji::category> choose_category(std::vector<std::shared_ptr<minji::category>>& categories)
	{
		std::weak_ptr<minji::category> chosen_cty;
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
					chosen_cty = categories[choice - 1];
			} while (!std::cin.eof() && std::cin.fail());
		}

		if (make_new && !std::cin.fail()) {
			std::cout << "create a category:\n";
			std::string name;
			do {
				std::cout << "  enter a name: ";
				std::getline(std::cin, name);
			} while (!std::cin.eof() && std::cin.fail());

			if (std::cin.eof())
				return std::weak_ptr<minji::category>();

			categories.emplace_back(std::make_shared<minji::category>(name));
			return categories.back();
		}

		return chosen_cty;
	}

	void print_menu(const std::weak_ptr<minji::category>& cty)
	{
		std::cout << "options for category " << cty.lock()->name() << "\n"
			"  (0) end\n"
			"  (1) add\n"
			"  (2) remove\n"
			"  (3) change_card\n"
			"  (4) change_category\n"
			"  (5) list\n"
			"\n"
			"  >> ";
	}

	menu::option parse_input(const std::weak_ptr<minji::category>& cty)
	{
		menu::option opt = menu::option::end;
		while (!(std::cin >> opt)) {
			// FIXME
		}

		return opt;
	}



	void exec_opt(menu::option opt)
	{
		// TODO
	}
}

void simple_menu()
{
	std::vector<std::shared_ptr<minji::category>> categories;
	std::weak_ptr<minji::category> chosen_cty;
	menu::option opt = menu::option::end;
	do {
		if (!chosen_cty.lock() || opt == menu::option::change_category) {
			chosen_cty = choose_category(categories);
			if (!chosen_cty.lock())
				break;
		}
		std::cout << '\n';
		opt = parse_input(chosen_cty);
		exec_opt(opt);
	} while (opt != menu::option::end);
}
