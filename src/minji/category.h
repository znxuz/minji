#pragma once

#include <string>
#include <vector>

#include "card.h"

namespace minji
{
	class category
	{
	public:
		category(std::string);
		std::string& name();
		const std::string& name() const;
		void add(std::unique_ptr<card>&&);
		void remove(std::vector<std::unique_ptr<card>>::iterator);
		void replace(std::vector<std::unique_ptr<card>>::iterator, std::unique_ptr<card>&&);
		void list() const;

	private:
		std::string _name;
		std::vector<std::unique_ptr<card>> _cards;
	};
}
