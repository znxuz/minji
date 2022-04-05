#include "card.h"

namespace minji
{
	card::card(std::string front, minji::card_back ans, std::string group) :
		_front(std::move(front)),
		_ans(std::make_unique<card_back>(std::move(ans))),
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

	card_back& minji::card::back()
	{
		return *_ans;
	}

	const card_back& minji::card::back() const
	{
		return const_cast<card*>(this)->back();
	}

	void card::print(std::ostream& os) const
	{
		os << *this;
	}

	std::ostream& operator<<(std::ostream& os, const card& c)
	{
		return (os << "# Front\n" << c.front() <<
				"\n"
				"\n"
				"# Back\n" <<
				c.back() <<
				"\n");
	}
}
