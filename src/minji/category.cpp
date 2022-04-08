#include <memory>

#include "category.h"

namespace minji
{
	category::category(std::string name) : _name(name)
	{ }

	void category::add(std::unique_ptr<card>&& c)
	{
		_cards.push_back(std::move(c));
	}

	void category::remove(std::vector<std::unique_ptr<card>>::iterator it)
	{
		_cards.erase(it);
	}

	void category::replace(std::vector<std::unique_ptr<card>>::iterator it, std::unique_ptr<card>&& c)
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
		std::for_each(begin(_cards), end(_cards), [](const auto& c) { std::cout << *c; });
	}
}
