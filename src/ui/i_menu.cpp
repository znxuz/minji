#include <functional>
#include <sstream>
#include <string>
#include <compare>
#include <ios>
#include <limits>
#include <memory>

#include "i_menu.h"

#include "menu_opt.h"
#include "../minji/category.h"
#include "../minji/answer_type.h"
#include "../minji/answer_factory.h"

namespace
{
	std::weak_ptr<minji::category> selected_cty;

	void print_menu()
	{
		std::cout << "\n[Menu] <" << selected_cty.lock()->name() << "> ";
		menu::print_opts();
	}

	menu::opt get_opt()
	{
		menu::opt opt;

		print_menu();
		if (!minji::parse_input(opt))
			return menu::opt::exit;
		std::cout << '\n';

		return opt;
	}

	void add_cty(std::vector<std::shared_ptr<minji::category>>& categories)
	{
		std::cout << "[Input] enter a name: \n";
		std::string name;
		auto same_name = [&categories](const std::string& name) {
			return std::find_if(begin(categories), end(categories),
					[&name](const auto& cty) { return cty->name() == name; })
				!= categories.end();
		};

		do {
			if (!name.empty())
				std::cerr << "[Error] category with the same name exists, try again\n";
			if (!minji::parse_input(name))
				return;
		} while (same_name(name));

		categories.emplace_back(std::make_shared<minji::category>(std::move(name)));
	}

	void list_cty(const std::vector<std::shared_ptr<minji::category>>& categories)
	{
		for (size_t i = 0; i < categories.size(); ++i) {
			std::cout << "  (" << (i + 1) << ") " << categories[i]->name() <<
				(selected_cty.lock() == categories[i] ? " (selected)\n" : "\n");
		}
	}

	void change_cty(std::vector<std::shared_ptr<minji::category>>& categories)
	{
		std::cout << "[Selection] categories\n";
		list_cty(categories);
		std::cout << "  (" << (categories.size() + 1) << ") make a new category\n";

		auto validater = [size=categories.size()](size_t input) { return --input > size; };
		size_t selected;
		if (!minji::parse_input(selected))
			return;
		--selected;

		if (selected == categories.size()) {
			add_cty(categories);
			if (categories.empty())
				return;
			selected_cty = categories.back();
		} else {
			selected_cty = categories[selected];
		}
	}

	void remove_cty(std::vector<std::shared_ptr<minji::category>>& categories)
	{
		std::cout << "[Selection] categories\n";
		list_cty(categories);
		std::cout << "  (" << (categories.size() + 1) << ") remove all\n";

		unsigned idx;
		auto validator = [size=categories.size()](unsigned idx) { return --idx > size; };
		if (!minji::parse_input(idx))
			return;
		--idx;

		if (idx == categories.size()) {
			categories.clear();
			return;
		}
		std::string name = std::move(categories[idx]->name());
		categories.erase(categories.begin() + idx);
		std::cout << "[Message] removed category: " << name << '\n';
	}

	void add_card()
	{
		std::string description;
		std::cout << "[Input] enter a description of the card:\n";
		if (!minji::parse_input(description))
			return;

		const auto& ans_types = minji::ans_types;
		std::stringstream ss;
		std::cout << "[Selection] answer types:\n";
		for (size_t i = 0; i <= ans_types.size(); ++i) {
			if (i < ans_types.size())
				ss << ans_types[i];
			else
				ss << "cancel";
			std::cout << "  (" << (i + 1) << ") " << ss.str() << '\n';
			ss.str(std::string()), ss.clear();
		}

		unsigned selected;
		auto validator = [size=ans_types.size()](auto selected) {
			return --selected >= ans_types.size();
		};
		if (!minji::parse_input(selected))
			return;
		--selected;

		std::string front;
		std::cout << "[Input] front card question:\n";
		if (!minji::parse_input(front))
			return;

		// TODO
		//  swtich in answer factory template varargs forward
		if (ans_types[selected] == minji::answer_type::plain) {
			std::string plain_ans;
			std::cout << "[Input] plain answer:\n";
			if (!minji::parse_input(plain_ans))
				return;
			selected_cty.lock()->add(minji::card(description, front,
						minji::make_answer(std::move(plain_ans)),
						selected_cty.lock()->name()));
		}
		std::cout << "[Message] added card to category <" << selected_cty.lock()->name() << ">\n";
	}

	void list_card()
	{
		selected_cty.lock()->list(std::cout);
	}

	void remove_card()
	{
		// TODO
	}

	void exec_opt(menu::opt opt, std::vector<std::shared_ptr<minji::category>>& categories)
	{
		switch (opt) {
			case menu::opt::add_card:
				add_card();
				break;
			case menu::opt::remove_card:
				remove_card();
				break;
			case menu::opt::change_card:
				// TODO
				break;
			case menu::opt::list_card:
				list_card();
				break;
			case menu::opt::add_cty:
				add_cty(categories);
				break;
			case menu::opt::remove_cty:
				remove_cty(categories);
				if (!selected_cty.lock())
					change_cty(categories);
				break;
			case menu::opt::change_cty:
				change_cty(categories);
				break;
			case menu::opt::list_cty:
				std::cout << "[List] categories:\n";
				list_cty(categories);
				std::cout << "press any key to continue..."; minji::flush();
				break;
			case menu::opt::exit:
				break;
		}
	}
}

void i_menu(std::vector<std::shared_ptr<minji::category>> categories)
{
	auto opt = menu::opt::change_cty;
	while (opt != menu::opt::exit) {
		exec_opt(opt, categories);
		if (!selected_cty.lock() || std::cin.eof())
			break;
		opt = get_opt();
	}
}
