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
	    explicit deck(std::string);
	    void add(card);
	    void remove(std::vector<card>::iterator);
	    void replace(std::vector<card>::iterator, card);
	    std::string& name();
	    const std::string& name() const;
	    void show_card(std::ostream&, size_t, card::reveal_back) const;
	    void show_answer(std::ostream&, size_t) const;
	    size_t size() const;
	    bool operator==(const deck& rhs) const;
	    std::vector<card>::iterator begin() { return cards_.begin(); }
	    std::vector<card>::iterator end() { return cards_.end() ;}
	    std::vector<card>::const_iterator cbegin() const { return cards_.cbegin(); }
	    std::vector<card>::const_iterator cend() const { return cards_.cend(); }

	private:
	    std::string name_;
	    std::vector<card> cards_;

    };
}
