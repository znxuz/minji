#pragma once

#include <iostream>

#include "card_back.h"

namespace minji
{
	class card
	{
	public:
		card(std::string front, card_back ans, std::string group = "");
		std::string& front();
		const std::string& front() const;
		card_back& back();
		const card_back& back() const;
		void print(std::ostream& os = std::cout) const;
		friend std::ostream& operator<<(std::ostream& os, const card& c);

	private:
		std::string _front;
		std::unique_ptr<card_back> _ans;
		std::string _group;
	};
}
