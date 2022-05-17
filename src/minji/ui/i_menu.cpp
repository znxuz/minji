#include <optional>
#include <functional>
#include <sstream>
#include <string>
#include <compare>
#include <ios>
#include <limits>
#include <memory>

#include "i_menu.h"

namespace
{
    using utils::parse_input;
    std::weak_ptr<minji::deck> current_deck;

    void practice_menu()
    {
	using practice::practice_opt;
	using practice::practice_opts;

	std::cout << "[practice] <" << current_deck.lock()->name()
	    << "> \n";
	for (size_t i = 0; i < practice_opts.size(); ++i)
	    std::cout << "  - " << practice_opts[i] << '\n';

	practice_opt opt;
	if (!parse_input(opt))
	    return;
	std::cout << opt << '\n';

	int count;
	switch (opt) {
	    case practice::practice_opt::numbered:
		{
		    std::cout << "[input] number of cards to practice:"
			"(enter 0 to cancel)\n";
		    if (!parse_input(count,
				[](int count) { return count < 0; }) ||
			    !count)
			return;
		    break;
		}
	    case practice::practice_opt::single_random:
		count = 1;
		break;
	    case practice::practice_opt::unlimited:
		count = -1;
		break;
	    case practice::practice_opt::exit:
		return;
	}

	practice::practice(current_deck.lock().get(), count);
    }

    std::optional<minji::answer_type> select_type()
    {
	using  minji::ans_types;

	std::cout << "[selection] answer types: (enter 0 to cancel)\n";
	for (size_t i = 0; i < ans_types.size(); ++i)
	    std::cout << "  (" << (i + 1) << ") " << ans_types[i] << '\n';

	unsigned idx;
	auto invalid_in = [limit = ans_types.size()](unsigned idx) {
	    return idx > limit;
	};
	if (!parse_input(idx, invalid_in) || !idx--)
	    return std::nullopt;
	return ans_types[idx];
    }

    void get_card_info(std::optional<std::string>& opt_descr,
	    std::optional<std::string>& opt_front,
	    std::optional<std::unique_ptr<minji::answer>>& opt_back)
    {
	std::cout << "[input] short description of the card:\n";
	std::string description;
	if (!parse_input(description))
	    return;
	opt_descr = std::move(description);

	std::cout << "[input] card front:\n";
	std::string front;
	if (!parse_input(front))
	    return;
	opt_front = std::move(front);

	auto type = select_type();
	if (!type)
	    return;
	switch (*type) {
	    case minji::answer_type::plain:
		{
		    std::string plain_ans;
		    std::cout << "[input] plain answer:\n";
		    if (!parse_input(plain_ans))
			return;
		    opt_back = minji::make_answer(std::move(plain_ans));
		    break;
		}
	    case minji::answer_type::multiple_choice:
		{
		    unsigned ans_count;
		    std::string sure;
		    auto invalid_in = [](const std::string& s) {
			return s.size() > 1 || (s != "y" && s != "n" && s != "c");
		    };
		    do {
			std::cout << "[input] total number of choices: "
			    "(enter 0 to cancel)\n";
			if (!parse_input(ans_count) || !ans_count)
			    return;
			std::cout << "[confirm] total choices: " << ans_count <<
			    ", sure? [(y)es/(n)o/(c)ancel]\n";
			if (!parse_input(sure, invalid_in) || sure == "c")
			    return;
		    } while (sure != "y");

		    std::vector<std::pair<std::string, bool>> choices(ans_count);
		    for (unsigned i = 0; i < ans_count; ++i) {
			std::cout << "[input] enter answer " << (i + 1) << ".\n";
			std::string ans;
			if (!parse_input(ans))
			    return;
			std::cout << "[confirm] is this answer the correct one?"
			    "[(y)es/(n)o/(c)ancel]\n";
			std::string confirm;
			if (!parse_input(confirm, invalid_in) || confirm == "c")
			    return;
			choices[i] = std::pair(std::move(ans), (confirm == "y"));
			std::cout << "[message] added the following answer: " <<
			    choices[i].first << " -> " << std::boolalpha <<
			    choices[i].second << "\n";
		    }
		    opt_back = minji::make_answer(std::move(choices));
		}
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
	std::cout << "[message] added card to deck <" <<
	    current_deck.lock()->name() << ">\n";
    }

    void list_card()
    {
	size_t cnt = 0;
	for (const auto& crd : *current_deck.lock())
	    std::cout << "(" << ++cnt << ") " << crd.description() << '\n';
    }

    void list_card_menu()
    {
	auto invalid_in = [size = current_deck.lock()->size()](size_t idx) {
	    return idx > size;
	};
	size_t idx = 0;
	do {
	    if (idx) {
		utils::clear_screen();
		current_deck.lock()->show_card(std::cout, idx - 1,
			minji::answer::reveal::yes);
		std::cout << '\n';
	    }
	    std::cout << "[list] cards:\n";
	    list_card();
	    std::cout << "[input] card index for content:"
		"(enter 0 to cancel)\n";
	} while (parse_input(idx, invalid_in) && idx != 0);
    }

    void change_card()
    {
	std::cout << "[select] card to replace: (enter 0 to cancel)\n";
	list_card();
	unsigned idx;
	auto invalid_in = [limit = current_deck.lock()->size()](size_t idx) {
	    return idx > limit;
	};
	if (!parse_input(idx, invalid_in) || !idx--)
	    return;

	auto c = make_card();
	if (!c)
	    return;
	current_deck.lock()->replace(current_deck.lock()->begin() + idx, *c);
    }

    void remove_card()
    {
	std::cout << "[selection] card to remove: (enter 0 to cancel)\n";
	list_card();
	unsigned idx;
	auto invalid_in = [size = current_deck.lock()->size()](size_t idx) {
	    return idx > size;
	};
	if (!parse_input(idx, invalid_in) || !idx--)
	    return;
	current_deck.lock()->remove(current_deck.lock()->begin() + idx);
	std::cout << "[message] card removed\n";
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
		std::cerr << "[error] deck with the same name exists,"
		    "try again\n";
	    if (!parse_input(name))
		return;
	} while (same_name(name));

	deck.emplace_back(std::make_shared<minji::deck>(std::move(name)));
    }

    void list_deck(const std::vector<std::shared_ptr<minji::deck>>& deck)
    {
	for (size_t i = 0; i < deck.size(); ++i) {
	    std::cout << "  (" << (i + 1) << ") " << deck[i]->name() <<
		(current_deck.lock() == deck[i] ? " (current)\n" : "\n");
	}
    }

    void change_deck(std::vector<std::shared_ptr<minji::deck>>& deck)
    {
	std::cout << "[selection] deck: (enter 0 to cancel)\n";
	list_deck(deck);
	std::cout << "  (" << (deck.size() + 1) << ") make a new deck\n";

	auto invalid_in = [limit = deck.size() + 1](size_t in) {
	    return in > limit;
	};
	size_t idx;
	if (!parse_input(idx, invalid_in) || !idx--)
	    return;

	if (idx == deck.size()) {
	    add_deck(deck);
	    if (deck.empty())
		return;
	    current_deck = deck.back();
	} else {
	    current_deck = deck[idx];
	}
    }

    void remove_deck(std::vector<std::shared_ptr<minji::deck>>& deck)
    {
	std::cout << "[selection] deck\n";
	list_deck(deck);
	std::cout << "  (" << (deck.size() + 1) << ") remove all\n";

	unsigned idx;
	auto invalid_in = [size = deck.size()](unsigned idx) {
	    return --idx > size;
	};
	if (!parse_input(idx, invalid_in))
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

    void main_menu()
    {
	utils::clear_screen();
	std::cout << "[menu] <" << current_deck.lock()->name() << ">\n";
	for (auto opt : ui::opts)
	    std::cout << "  - " << opt << '\n';
    }

    ui::opt get_opt()
    {
	ui::opt opt;

	main_menu();
	if (!parse_input(opt))
	    return ui::opt::exit;
	std::cout << '\n';

	return opt;
    }

    void exec_opt(ui::opt opt,
	    std::vector<std::shared_ptr<minji::deck>>& decks)
    {
	utils::clear_screen();
	switch (opt) {
	    case ui::opt::practice:
		practice_menu();
		break;
	    case ui::opt::add_card:
		add_card();
		break;
	    case ui::opt::list_card:
		list_card_menu();
		break;
	    case ui::opt::change_card:
		change_card();
		break;
	    case ui::opt::remove_card:
		remove_card();
		break;
	    case ui::opt::add_deck:
		add_deck(decks);
		break;
	    case ui::opt::list_deck:
		std::cout << "[list] decks:\n";
		list_deck(decks);
		std::cout << "press Enter to continue...\n";
		utils::flush();
		break;
	    case ui::opt::change_deck:
		change_deck(decks);
		break;
	    case ui::opt::remove_deck:
		remove_deck(decks);
		if (!current_deck.lock())
		    change_deck(decks);
		break;
	    case ui::opt::exit:
		break;
	}
    }

}

namespace ui
{
    void i_menu(std::vector<std::shared_ptr<minji::deck>> decks)
    {
	auto opt = ui::opt::change_deck;
	while (opt != ui::opt::exit) {
	    exec_opt(opt, decks);
	    if (!current_deck.lock() || std::cin.eof())
		break;
	    opt = get_opt();
	}
    }
}
