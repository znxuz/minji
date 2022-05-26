#include "practice.h"

namespace
{
    static auto gen = std::mt19937(std::random_device()());
    using utils::clear_screen;

    enum class choice
    {
	next = 'n', prev = 'p', cancel = 'c'
    };

    constexpr static std::array<choice, 3> choices {
	choice::next, choice::prev, choice::cancel
    };

    std::ostream& operator<<(std::ostream& os, const choice c)
    {
	switch (c) {
	    case choice::next:
		return (os << "(n)ext");
	    case choice::prev:
		return (os << "(p)revious");
	    case choice::cancel:
		return (os << "(c)ancel");
	}
	return os;
    }

    std::istream& operator>>(std::istream& is, choice& c)
    {
	char in;
	is >> in;
	c = static_cast<choice>(in);
	if (std::find(begin(choices), end(choices), c) == end(choices))
	    is.setstate(std::ios::failbit);

	return is;
    }

    inline void print_choices()
    {
	std::cout << "[select]\n";
	for (auto c : choices)
	    std::cout << "  " << c <<
		(c == choice::next ? " (default)" : "") << '\n';
    }

    void start(std::deque<const minji::card*>& randomized_deck, int count)
    {
	if (!count || std::cin.eof())
	    return;

	clear_screen();

	const auto* crd = randomized_deck.front();
	crd->show(std::cout, minji::answer::reveal::no);
	std::cout << "\n---\n\n";

	std::cout << "[confirm] press Enter to show the answer";
	if (std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
		    '\n') && !std::cin.eof()) {
	    clear_screen();
	    crd->show(std::cout, minji::answer::reveal::yes);
	    std::cout << "\n---\n\n";

	    print_choices();
	    choice c = choice::next;
	    if (utils::parse_input_return_empty(c)) {
		switch (c) {
		    case choice::next:
			randomized_deck.pop_front();
			randomized_deck.push_back(crd);
			break;
		    case choice::prev:
			randomized_deck.push_front(randomized_deck.back());
			randomized_deck.pop_back();
			break;
		    case choice::cancel:
			return;
		}
	    }
	}

	start(randomized_deck, --count);
    }
}

namespace practice
{
    void practice(const minji::deck* deck, int count)
    {
	std::deque<const minji::card*> randomized_deck(deck->size());
	for (size_t i = 0; i < deck->size(); ++i)
	    randomized_deck[i] = &(*deck)[i];
	std::shuffle(begin(randomized_deck), end(randomized_deck), gen);

	start(randomized_deck, count);
    }
}
