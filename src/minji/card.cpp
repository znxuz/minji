#include "card.h"

namespace minji
{
	card::card(std::string front, std::unique_ptr<answer>&& ans, std::string category) :
		_front(std::move(front)),
		_ans(std::move(ans)),
		_category(std::move(category))
	{ }

	std::string& card::front()
	{
		return _front;
	}

	const std::string& card::front() const
	{
		return const_cast<card*>(this)->front();
	}

	answer& card::back()
	{
		return *_ans;
	}

	const answer& card::back() const
	{
		return const_cast<card*>(this)->back();
	}

	bool card::operator==(const card& c) const
	{
		return this == &c ||
			(this->_front == c._front &&
			 this->_ans == c._ans &&
			 this->_category == c._category);
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
