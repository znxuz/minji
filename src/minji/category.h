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
		void add(card&&);
		void remove(std::vector<card>::iterator);
		void replace(std::vector<card>::iterator, card);
		void list() const;
		bool operator==(const category& rhs) const;

	private:
		std::string _name;
		std::vector<card> _cards;
	};
}
