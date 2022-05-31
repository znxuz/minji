#include "collection.h"

namespace minji
{
    collection::collection(std::vector<collection::value_type>&& decks) :
	decks_(std::move(decks))
    {}

    void collection::add_deck(collection::value_type&& deck)
    {
	decks_.push_back(std::move(deck));
    }

    void collection::erase(std::vector<collection::value_type>::iterator it)
    {
	decks_.erase(it);
    }

    void collection::clear()
    {
	decks_.clear();
    }

    size_t collection::size() const
    {
	return decks_.size();
    }

    bool collection::empty() const
    {
	return !this->size();
    }

    collection::value_type& collection::operator[](size_t i)
    {
	return decks_[i];
    }

    const collection::value_type& collection::operator[](size_t i) const
    {
	return const_cast<collection*>(this)->operator[](i);
    }

    collection::value_type& collection::back()
    {
	return decks_.back();
    }

    const collection::value_type& collection::back() const
    {
	return decks_.back();
    }

    std::vector<collection::value_type>::iterator collection::begin()
    {
	return decks_.begin();
    }

    std::vector<collection::value_type>::iterator collection::end()
    {
	return decks_.end();
    }

    std::vector<collection::value_type>::const_iterator collection::begin() const
    {
	return decks_.begin();
    }

    std::vector<collection::value_type>::const_iterator collection::end() const
    {
	return decks_.end();
    }

}
