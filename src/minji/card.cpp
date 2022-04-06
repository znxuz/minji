#include "card.h"

namespace minji
{
	card::card(std::string front, std::unique_ptr<answer> ans, std::string group) :
		_front(std::move(front)),
		_ans(std::move(ans)),
		_group(std::move(group))
	{ }

	std::string& card::front()
	{
		return _front;
	}

	const std::string& card::front() const
	{
		return const_cast<card*>(this)->front();
	}

	answer& minji::card::back()
	{
		return *_ans;
	}

	const answer& minji::card::back() const
	{
		return const_cast<card*>(this)->back();
	}

	std::ostream& operator<<(std::ostream& os, const minji::card& c)
	{
		return (os << "# Front\n" << c.front() <<
				"\n"
				"\n"
				"# Back\n" <<
				c.back() <<
				"\n");
	}
}
