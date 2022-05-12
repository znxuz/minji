#include "practice.h"

namespace
{
    static std::mt19937_64 gen;
}

namespace practice
{
    void practice(const minji::deck* deck, int count)
    {
	if (!count || std::cin.eof())
	    return;

	std::system("clear");

	size_t idx = gen() % deck->size();
	deck->show_card(std::cout, idx, minji::card::reveal_back::no);
	std::cout << "[confirm] press any key to show the answer";
	if (std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n')) {
	    deck->show_answer(std::cout, idx);
	    std::cout << '\n';
	    std::cout << "[confirm] press any key to continue...";
	    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	practice(deck, --count);
    }
}
