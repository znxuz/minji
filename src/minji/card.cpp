#include "card.h"

namespace minji
{
    card::card(const card& c) : _description(c._description),
    _front(c._front), _deck_name(c._deck_name)
    {
	_back = c.back().clone();
    }

    card& card::operator=(const card& c)
    {
	card cpy = c;
	using std::swap;
	swap(this->_description, cpy._description);
	swap(this->_front, cpy._front);
	swap(this->_back, cpy._back);
	swap(this->_deck_name, cpy._deck_name);

	return *this;
    }

    std::string& card::description()
    {
        return _description;
    }

    const std::string& card::description() const
    {
        return const_cast<card*>(this)->description();
    }

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
        return *_back;
    }

    const answer& card::back() const
    {
        return const_cast<card*>(this)->back();
    }

    bool card::operator==(const card& c) const
    {
        return this == &c ||
            (this->_front == c._front &&
             this->_back == c._back &&
             this->_deck_name == c._deck_name);
    }

    std::ostream& operator<<(std::ostream& os, const card& c)
    {
        return (os <<
                "# Description\n" << "\t" << c.description() << "\n"
                "# Front\n" << "\t" << c.front() << "\n"
                "# Back\n" << "\t" << c.back() << "\n");
    }

    card::card(std::string description, std::string front,
            std::unique_ptr<answer>&& ans, std::string deck_name) noexcept :
        _description(std::move(description)),
        _front(std::move(front)),
        _back(std::move(ans)),
        _deck_name(std::move(deck_name))
        {}

    card_builder::card_builder(std::string deck_name) : _deck_name(deck_name)
    {}

    card_builder card_builder::init(std::string deck_name)
    {
        return card_builder(std::move(deck_name));
    }

    card_builder& card_builder::description(std::string description)
    {
        _description = std::move(description);
        return *this;
    }

    card_builder& card_builder::front(std::string front)
    {
        _front = std::move(front);
        return *this;
    }

    card_builder& card_builder::back(std::unique_ptr<answer>&& ans)
    {
        _ans = std::move(ans);
        return *this;
    }

    card card_builder::build()
    {
        return card(std::move(_description), std::move(_front),
                std::move(_ans), std::move(_deck_name));
    }
}
