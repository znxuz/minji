#pragma once

#include <iostream>

namespace menu
{
	enum class option
	{
		end = 0, add, remove, change_card, change_category, list
	};

	std::istream& operator>>(std::istream& is, menu::option& opt);
	std::ostream& operator<<(std::ostream& os, const menu::option& opt);
}
