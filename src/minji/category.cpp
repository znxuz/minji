#include <memory>

#include "category.h"

namespace minji
{
	category::category(std::string name) : _name(name)
	{}

	void category::add(card&& c)
	{
		_cards.push_back(std::move(c));
	}

	void category::remove(std::vector<card>::iterator it)
	{
		_cards.erase(it);
	}

	void category::replace(std::vector<card>::iterator it, card c)
	{
		*it = std::move(c);
	}

	std::string& category::name()
	{
		return _name;
	}

	const std::string& category::name() const
	{
		return const_cast<category*>(this)->name();
	}

	void category::list() const
	{
		std::for_each(begin(_cards), end(_cards), [](const auto& c) { std::cout << c; });
	}

	bool category::operator==(const category& rhs) const
	{
		return this->_name == rhs._name && this->_cards == rhs._cards;
	}
}
