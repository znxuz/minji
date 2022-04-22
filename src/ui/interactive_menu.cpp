#include <compare>
#include <ios>
#include <limits>
#include <memory>

#include "interactive_menu.h"
#include "../minji/category.h"
#include "menu_option.h"

namespace
{
	void flush()
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	menu::opt get_opt()
	{
		menu::opt opt;

		menu::print_opts();
		while (std::cout << "  > " && !(std::cin >> opt)) {
			if (std::cin.eof())
				return menu::opt::exit;
			std::cerr << "invalid option, try again\n";
			flush();
		}
		flush();

		return opt;
	}

	void add_cty(std::vector<std::shared_ptr<minji::category>>& categories)
	{
		std::string name;
		
		while (std::cout << "enter a name: " &&
				(!std::getline(std::cin, name) || std::find_if(begin(categories), end(categories),
							[&name](const auto& cty) { return cty->name() == name; }) != end(categories))){
			if (std::cin.eof())
				return;
			if (!std::cin.fail())
				std::cerr << "category with the same name exists, try again\n";
			else
				std::cerr << "invalid input, try again\n";
		}
		categories.emplace_back(std::make_shared<minji::category>(name));
	}

	void change_cty(std::weak_ptr<minji::category>& cty,
			std::vector<std::shared_ptr<minji::category>>& categories)
	{
		std::cout << "select one category or make a new category:\n";
		for (size_t i = 0; i <= categories.size(); ++i) {
			std::string entry = (i < categories.size() ?
					categories[i]->name() + (cty.lock() == categories[i] ? " (selected)" : "") :
					"make a new category");
			std::cout << "  (" << (i + 1) << ") " << entry << '\n';
		}

		size_t selected;
		while (std::cout << "  > " && (!(std::cin >> selected) || --selected > categories.size())) {
			if (std::cin.eof())
				return;
			std::cerr << "invalid input, try again\n";
			flush();
		}
		flush();

		if (selected == categories.size()) {
			add_cty(categories);
			cty = categories.back();
		} else {
			cty = categories[selected];
		}
	}

	void list_cty(const std::vector<std::shared_ptr<minji::category>>& categories)
	{
		std::cout << "saved categories:\n";
		for (size_t i = 0; i < categories.size(); ++i)
			std::cout << "  (" << (i + 1) << ") " << categories[i]->name() << '\n';
	}

	void remove_cty(std::vector<std::shared_ptr<minji::category>>& categories)
	{
		list_cty(categories);
		unsigned idx;
		while (std::cout << "  > " && (!(std::cin >> idx) || --idx >= categories.size())) {
			if (std::cin.eof())
				return;
			std::cerr << "invalid input, try again\n";
			flush();
		}
		flush();

		std::string name = std::move(categories[idx]->name());
		categories.erase(categories.begin() + idx);
		std::cout << "  removed category: " << name << '\n';
	}

	void exec_opt(menu::opt opt, std::weak_ptr<minji::category>& cty,
			std::vector<std::shared_ptr<minji::category>>& categories)
	{
		switch (opt) {
			case menu::opt::change_cty:
				change_cty(cty, categories);
				break;
			case menu::opt::add_cty:
				add_cty(categories);
				break;
			case menu::opt::list_cty:
				list_cty(categories);
				std::cout << "  press any to continue";
				flush();
				break;
			case menu::opt::remove_cty:
				remove_cty(categories);
				if (!cty.lock())
					change_cty(cty, categories);
				break;

			// TODO
			default:
				break;
		}
	}
}

void interactive_menu(std::vector<std::shared_ptr<minji::category>> categories)
{
	std::weak_ptr<minji::category> cty;
	auto opt = menu::opt::change_cty;
	while (opt != menu::opt::exit) {
		exec_opt(opt, cty, categories);
		if (!cty.lock() || std::cin.eof())
			break;
		std::cout << "[" << cty.lock()->name() << "] ";
		opt = get_opt();
	}
}
