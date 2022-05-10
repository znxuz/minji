#include <memory>

#include "deck.h"

namespace minji
{
    deck::deck(std::string name) : _name(name)
    {}

    void deck::add(card c)
    {
	_cards.push_back(std::move(c));
    }

    void deck::remove(std::vector<card>::iterator it)
    {
	_cards.erase(it);
    }

    void deck::replace(std::vector<card>::iterator it, card c)
    {
	*it = std::move(c);
    }

    std::string& deck::name()
    {
	return _name;
    }

    const std::string& deck::name() const
    {
	return const_cast<deck*>(this)->name();
    }

    void deck::show_card(std::ostream& os, size_t idx) const
    {
	os << _cards[idx];
    }

    size_t deck::size() const
    {
	return _cards.size();
    }

    bool deck::operator==(const deck& rhs) const
    {
	return this->_name == rhs._name && this->_cards == rhs._cards;
    }
}
