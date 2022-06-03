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
	if (!utils::parse_input(opt))
	    return;
	std::cout << opt << '\n';

	int count;
	switch (opt) {
	    case practice::practice_opt::numbered:
		{
		    std::cout << "[input] number of cards to practice:"
			"(enter 0 or nothing to cancel)\n";
		    if (!utils::parse_input(count, []
				(int count) { return count < 0; }) ||
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

    void parse_card_info(std::optional<std::string>& opt_descr,
	    std::optional<std::string>& opt_front,
	    std::optional<std::unique_ptr<minji::answer>>& opt_back)
    {
	std::cout << "[input] short description of the card:\n";
	std::string description;
	if (!utils::parse_input_getline(description))
	    return;
	opt_descr = std::move(description);

	std::cout << "[input] card front:\n";
	std::string front;
	if (!utils::parse_input_getline(front))
	    return;
	opt_front = std::move(front);

	using  minji::ans_types;
	std::cout << "[selection] answer types: "
	    "(enter nothing to cancel)\n";
	for (size_t i = 0; i < ans_types.size(); ++i)
	    std::cout << "  (" << static_cast<char>(ans_types[i]) << ") " <<
		ans_types[i] << '\n';
	std::optional<minji::answer_type> type;
	if (!utils::parse_input(*type))
	    return;

	switch (*type) {
	    case minji::answer_type::plain:
		{
		    std::string plain_ans;
		    std::cout << "[input] plain answer:\n";
		    if (!utils::parse_input_getline(plain_ans))
			return;
		    opt_back = minji::make_answer(std::move(plain_ans));
		    break;
		}
	    case minji::answer_type::multiple_choice:
		{
		    unsigned ans_count;
		    char sure;
		    auto invalid_confirm = [](char c) {
			return c != 'y' && c != 'n' && c != 'c';
		    };
		    do {
			std::cout << "[input] total number of choices: "
			    "(enter 0 or nothing to cancel)\n";
			if (!utils::parse_input(ans_count) ||
				!ans_count)
			    return;
			std::cout << "[confirm] total choices: " << ans_count <<
			    ", sure? [(y)es/(n)o/(c)ancel]\n";
			while (!utils::parse_input(sure, invalid_confirm));
			// FIXME
			if (sure == 'c')
			    return;
		    } while (sure != 'y');

		    std::vector<std::pair<std::string, bool>> choices(ans_count);
		    for (unsigned i = 0; i < ans_count; ++i) {
			std::cout << "[input] enter answer " << (i + 1) << ".\n";
			std::string ans;
			if (!utils::parse_input_getline(ans))
			    return;
			std::cout << "[confirm] is this answer the correct one?"
			    "[(y)es/(n)o/(c)ancel]\n";
			char confirm;
			while (!utils::parse_input(confirm, invalid_confirm));
			if (confirm == 'c')
			    return;
			choices[i] = std::pair(std::move(ans), (confirm == 'y'));
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
	// std::tuple
	std::optional<std::string> description, front;
	std::optional<std::unique_ptr<minji::answer>> back;

	parse_card_info(description, front, back);
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
	size_t idx = 0;
	auto invalid_in = [size = current_deck.lock()->size()]
	    (size_t idx) {
		return idx > size;
	    };
	do {
	    if (idx) {
		utils::clear_screen();
		current_deck.lock()->show_card(std::cout, idx - 1,
			minji::answer::reveal::yes);
		std::cout << '\n';
	    }
	    std::cout << "[list] cards:\n";
	    list_card();
	    std::cout << "[input] card index for the content: "
		"(enter 0 or nothing to cancel)\n";
	} while (utils::parse_input(idx, invalid_in) && idx);
    }

    void change_card()
    {
	std::cout << "[select] card to replace: "
	    "(enter 0 or nothing to cancel)\n";
	list_card();
	unsigned idx;
	auto invalid_in = [limit = current_deck.lock()->size()](size_t idx) {
	    return idx > limit;
	};
	if (!utils::parse_input(idx, invalid_in) || !idx--)
	    return;

	auto c = make_card();
	if (!c)
	    return;
	current_deck.lock()->replace(current_deck.lock()->begin() + idx, *c);
    }

    void remove_card()
    {
	std::cout << "[selection] card to remove: "
	    "(enter 0 or nothing to cancel)\n";
	list_card();
	unsigned idx;
	auto invalid_in = [size = current_deck.lock()->size()](size_t idx) {
	    return idx > size;
	};
	if (!utils::parse_input(idx, invalid_in) || !idx--)
	    return;

	current_deck.lock()->remove(current_deck.lock()->begin() + idx);
	std::cout << "[message] card removed\n";
    }

    void import_markdown(minji::collection& clt)
    {
	std::filesystem::path p;
	do {
	    if (!p.empty())
		std::cerr << "[message] path invalid, try again\n";
	    std::cout << "[input] file path:\n";
	    if (!utils::parse_input(p))
		return;
	} while (!std::filesystem::exists(p));

	std::cout << "[input] deck name:\n";
	std::string deck_name;
	if (!utils::parse_input_getline(deck_name))
	    return;

	auto deck = io::parse_markdown(p, deck_name);
	if (!deck) {
	    std::cerr << "[message] error while parsing, no deck is added\n";
	    return;
	}

	std::cout << "[message] added " + deck->name() + " into the decks\n";
	clt.add_deck(std::move(deck));
    }

    void add_deck(minji::collection& clt)
    {
	using std::begin, std::end;

	std::cout << "[input] enter a name: \n";
	std::string name;
	auto same_name = [&clt](const std::string& name) {
	    return std::find_if(begin(clt), end(clt),
		    [&name](const auto& deck) { return deck->name() == name; })
		!= clt.end();
	};
	do {
	    if (!name.empty())
		std::cerr << "[error] deck with the same name exists,"
		    "try again\n";
	    if (!utils::parse_input_getline(name))
		return;
	} while (same_name(name));

	clt.add_deck(std::make_shared<minji::deck>(std::move(name)));
    }

    void list_deck(const minji::collection& clt)
    {
	for (size_t i = 0; i < clt.size(); ++i) {
	    std::cout << "  (" << (i + 1) << ") " << clt[i]->name() <<
		(current_deck.lock() == clt[i] ? " (current)\n" : "\n");
	}
    }

    void change_deck(minji::collection& clt)
    {
	std::cout << "[selection] deck: (enter 0 or nothing to cancel)\n";
	list_deck(clt);
	std::cout << "  (" << (clt.size() + 1) << ") make a new deck\n";
	std::cout << "  (" << (clt.size() + 2) << ") import a deck\n";

	auto invalid_in = [limit = clt.size() + 2](size_t in) {
	    return in > limit;
	};
	size_t idx;
	if (!utils::parse_input(idx, invalid_in) || !idx--)
	    return;

	if (idx < clt.size()) {
	    current_deck = clt[idx];
	    return;
	}

	if (idx == clt.size())
	    add_deck(clt);
	else
	    import_markdown(clt);
	change_deck(clt);
    }

    void remove_deck(minji::collection& clt)
    {
	std::cout << "[selection] deck\n";
	list_deck(clt);
	std::cout << "  (" << (clt.size() + 1) << ") remove all\n";

	unsigned idx;
	auto invalid_in = [size = clt.size()](unsigned idx) {
	    return --idx > size;
	};
	if (!utils::parse_input(idx, invalid_in))
	    return;
	--idx;

	if (idx == clt.size()) {
	    clt.clear();
	    return;
	}
	std::string name = std::move(clt[idx]->name());
	clt.erase(clt.begin() + idx);
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
	if (!utils::parse_input(opt))
	    return ui::opt::exit;
	std::cout << '\n';

	return opt;
    }

    void exec_opt(ui::opt opt, minji::collection& clt)
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
		if (!current_deck.lock()->size()) {
		    std::cout << "[message] deck is empty\n";
		    utils::prompt_enter();
		    return;
		}
		list_card_menu();
		break;
	    case ui::opt::change_card:
		change_card();
		break;
	    case ui::opt::remove_card:
		remove_card();
		break;
	    case ui::opt::add_deck:
		add_deck(clt);
		break;
	    case ui::opt::list_deck:
		std::cout << "[list] decks:\n";
		list_deck(clt);
		utils::prompt_enter();
		break;
	    case ui::opt::change_deck:
		change_deck(clt);
		break;
	    case ui::opt::remove_deck:
		remove_deck(clt);
		if (!current_deck.lock())
		    change_deck(clt);
		break;
	    case ui::opt::import_deck:
		import_markdown(clt);
		break;
	    case ui::opt::export_deck:
		io::export_markdown(current_deck.lock().get());
	    case ui::opt::exit:
		break;
	}
    }

}

namespace ui
{
    void i_menu(minji::collection& clt)
    {
	auto opt = ui::opt::change_deck;
	while (opt != ui::opt::exit) {
	    exec_opt(opt, clt);
	    if (!current_deck.lock() || std::cin.eof())
		break;
	    opt = get_opt();
	}
    }
}
