#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "card.h"

namespace minji
{
    class deck
    {
	public:
	    deck(std::string);
	    void add(card);
	    void remove(std::vector<card>::iterator);
	    void replace(std::vector<card>::iterator, card);
	    std::string& name();
	    const std::string& name() const;
	    void show_card(std::ostream&, size_t) const;
	    size_t size() const;
	    bool operator==(const deck& rhs) const;
	    std::vector<card>::iterator begin() { return _cards.begin(); }
	    std::vector<card>::iterator end() { return _cards.end() ;}
	    std::vector<card>::const_iterator cbegin() const { return _cards.cbegin(); }
	    std::vector<card>::const_iterator cend() const { return _cards.cend(); }

	private:
	    std::string _name;
	    std::vector<card> _cards;
    };
}
