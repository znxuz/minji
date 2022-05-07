#include <optional>
#include <functional>
#include <sstream>
#include <string>
#include <compare>
#include <ios>
#include <limits>
#include <memory>

#include "i_menu.h"

#include "menu_opt.h"
#include "../minji/deck.h"
#include "../minji/answer_type.h"
#include "../minji/answer_factory.h"

namespace
{
    std::weak_ptr<minji::deck> current_deck;

    void print_menu()
    {
	std::cout << "\n[menu] <" << current_deck.lock()->name() << "> ";
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

    void add_deck(std::vector<std::shared_ptr<minji::deck>>& deck)
    {
	std::cout << "[input] enter a name: \n";
	std::string name;
	auto same_name = [&deck](const std::string& name) {
	    return std::find_if(begin(deck), end(deck),
		    [&name](const auto& deck) { return deck->name() == name; })
		!= deck.end();
	};

	do {
	    if (!name.empty())
		std::cerr << "[error] deck with the same name exists, try again\n";
	    if (!minji::parse_input(name))
		return;
	} while (same_name(name));

	deck.emplace_back(std::make_shared<minji::deck>(std::move(name)));
    }

    void list_deck(const std::vector<std::shared_ptr<minji::deck>>& deck)
    {
	for (size_t i = 0; i < deck.size(); ++i) {
	    std::cout << "  (" << (i + 1) << ") " << deck[i]->name() <<
		(current_deck.lock() == deck[i] ? " (selected)\n" : "\n");
	}
    }

    void change_deck(std::vector<std::shared_ptr<minji::deck>>& deck)
    {
	std::cout << "[selection] deck\n";
	list_deck(deck);
	std::cout << "  (" << (deck.size() + 1) << ") make a new deck\n";

	auto validator = [size=deck.size()](size_t input) { return input - 1 > size; };
	size_t selected;
	if (!minji::parse_input(selected, validator))
	    return;
	--selected;

	if (selected == deck.size()) {
	    add_deck(deck);
	    if (deck.empty())
		return;
	    current_deck = deck.back();
	} else {
	    current_deck = deck[selected];
	}
    }

    void remove_deck(std::vector<std::shared_ptr<minji::deck>>& deck)
    {
	std::cout << "[selection] deck\n";
	list_deck(deck);
	std::cout << "  (" << (deck.size() + 1) << ") remove all\n";

	unsigned idx;
	auto validator = [size=deck.size()](unsigned idx) { return --idx > size; };
	if (!minji::parse_input(idx, validator))
	    return;
	--idx;

	if (idx == deck.size()) {
	    deck.clear();
	    return;
	}
	std::string name = std::move(deck[idx]->name());
	deck.erase(deck.begin() + idx);
	std::cout << "[message] removed deck: " << name << '\n';
    }

    std::optional<minji::answer_type> select_type()
    {
	const auto& ans_types = minji::ans_types;
	std::stringstream ss;
	std::cout << "[selection] answer types:\n";
	for (size_t i = 0; i <= ans_types.size(); ++i) {
	    if (i < ans_types.size())
		ss << ans_types[i];
	    else
		ss << "cancel";
	    std::cout << "  (" << (i + 1) << ") " << ss.str() << '\n';
	    ss.str(std::string()), ss.clear();
	}
	unsigned selected;
	auto validator = [size=ans_types.size()](unsigned selected) {
	    return selected - 1 > ans_types.size();
	};
	if (!minji::parse_input(selected, validator))
	    return std::nullopt;
	return ans_types[--selected];
    }

    void get_card_info(std::optional<std::string>& opt_descr,
	    std::optional<std::string>& opt_front,
	    std::optional<std::unique_ptr<minji::answer>>& opt_back)
    {
	std::cout << "[input] short description of the card:\n";
	std::string description;
	if (std::cout << minji::prompt && !std::getline(std::cin, description))
	    return;
	opt_descr = std::move(description);

	std::cout << "[input] card front:\n";
	std::string front;
	if (std::cout << minji::prompt && !std::getline(std::cin, front))
	    return;
	opt_front = std::move(front);

	auto type = select_type();
	if (!type)
	    return;
	switch (*type) {
	    case minji::answer_type::plain:
		std::string plain_ans;
		std::cout << "[input] plain answer:\n";
		if (!minji::parse_input(plain_ans))
		    return;
		opt_back = minji::make_answer(plain_ans);
		break;
	}
    }

    std::optional<minji::card> make_card()
    {
	std::optional<std::string> description, front;
	std::optional<std::unique_ptr<minji::answer>> back;
	get_card_info(description, front, back);
	if (!description || !front || !back)
	    return std::nullopt;

	return minji::card_builder::init(current_deck.lock()->name())
	    .description(*description)
	    .front(*front)
	    .back(std::move(*back))
	    .build();
    }

    void add_card()
    {
	auto c = make_card();
	if (!c)
	    return;
	current_deck.lock()->add(*c);
	std::cout << "[message] added card to deck <" << current_deck.lock()->name() << ">\n";
    }

    void list_card()
    {
	size_t cnt = 0;
	for (const auto& crd : *current_deck.lock())
	    std::cout << "(" << ++cnt << ") " << crd.description() << '\n';
    }

    void remove_card()
    {
	std::cout << "[selection] card to remove:\n";
	list_card();
	unsigned idx;
	auto validator = [size=current_deck.lock()->size()](size_t idx) { return idx - 1 > size; };
	if (!minji::parse_input(idx, validator))
	    return;
	current_deck.lock()->remove(current_deck.lock()->begin() + idx);
	std::cout << "[message] card removed\n";
    }

    void change_card()
    {
	std::cout << "[select] card to remove:\n";
	list_card();
	unsigned idx;
	auto validator = [size=current_deck.lock()->size()](size_t idx) { return idx - 1 >= size; };
	if (!minji::parse_input(idx, validator))
	    return;
	--idx;

	auto c = make_card();
	if (!c)
	    return;
	current_deck.lock()->replace(current_deck.lock()->begin() + idx, *c);
    }

    void exec_opt(menu::opt opt, std::vector<std::shared_ptr<minji::deck>>& decks)
    {
	switch (opt) {
	    case menu::opt::add_card:
		add_card();
		break;
	    case menu::opt::remove_card:
		remove_card();
		break;
	    case menu::opt::change_card:
		change_card();
		break;
	    case menu::opt::list_card:
		std::cout << "[List] deck:\n";
		list_card();
		std::cout << "press any key to continue..."; minji::flush();
		break;
	    case menu::opt::add_deck:
		add_deck(decks);
		break;
	    case menu::opt::remove_deck:
		remove_deck(decks);
		if (!current_deck.lock())
		    change_deck(decks);
		break;
	    case menu::opt::change_deck:
		change_deck(decks);
		break;
	    case menu::opt::list_deck:
		std::cout << "[List] deck:\n";
		list_deck(decks);
		std::cout << "press any key to continue..."; minji::flush();
		break;
	    case menu::opt::exit:
		break;
	}
    }
}

void i_menu(std::vector<std::shared_ptr<minji::deck>> decks)
{
    auto opt = menu::opt::change_deck;
    while (opt != menu::opt::exit) {
	exec_opt(opt, decks);
	if (!current_deck.lock() || std::cin.eof())
	    break;
	opt = get_opt();
    }
}
