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
	    const std::string& name() const;
	    std::string& name();
	    void show_card(std::ostream&, size_t, answer::reveal) const;
	    void show_answer(std::ostream&, size_t) const;
	    size_t size() const;
	    bool operator==(const deck& rhs) const;
	    const card& operator[](size_t i) const;
	    card& operator[](size_t i);

	    std::vector<card>::iterator begin();
	    std::vector<card>::const_iterator begin() const;
	    std::vector<card>::iterator end();
	    std::vector<card>::const_iterator end() const;

	private:
	    std::string name_;
	    std::vector<card> cards_;
    };
}
