#pragma once

#include <vector>
#include <memory>

#include "deck.h"

namespace minji
{
    class collection
    {
    public:
	using value_type = std::shared_ptr<deck>;

	collection(std::vector<value_type>&&);
	collection(collection&) = delete;
	collection(collection&&) = default;
	collection& operator=(const collection&) = delete;
	collection& operator=(collection&&) = default;

	void add_deck(value_type&&);
	void erase(std::vector<value_type>::iterator);
	void clear();
	size_t size() const;
	bool empty() const;

	value_type& operator[](size_t i);
	const value_type& operator[](size_t i) const;

	value_type& back();
	const value_type& back() const;
	std::vector<value_type>::iterator begin();
	std::vector<value_type>::const_iterator begin() const;
	std::vector<value_type>::iterator end();
	std::vector<value_type>::const_iterator end() const;

    private:
	std::vector<value_type> decks_;
    };
}
