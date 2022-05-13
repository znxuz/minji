#include "practice.h"

namespace
{
    static auto gen = std::mt19937(std::random_device()());
}

namespace practice
{
    void loop_through(std::deque<const minji::card*>& que, int count)
    {
	if (!count || std::cin.eof())
	    return;

	std::system("clear");

	const auto* crd = que.front();
	que.pop_front();
	que.push_back(crd);
	crd->show(std::cout, minji::answer::reveal::no);
	std::cout << "[confirm] press any key to show the answer";
	if (std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n')
		&& !std::cin.eof()) {
	    std::system("clear");
	    crd->show(std::cout, minji::answer::reveal::yes);
	    std::cout << "[confirm] press any key to continue";
	    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	loop_through(que, --count);
    }

    void practice(const minji::deck* deck, int count)
    {
	std::deque<const minji::card*> que(deck->size());
	size_t i = 0;
	for (const auto& c : *deck)
	    que[i++] = &c;

	std::shuffle(begin(que), end(que), gen);
	loop_through(que, count);
    }
}
