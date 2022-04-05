#pragma once

#include <iostream>

namespace menu
{
	enum class option
	{
		end, add, remove, change, list
	};

	std::istream& operator>>(std::istream& is, menu::option& opt);
	std::ostream& operator<<(std::ostream& os, const menu::option& opt);
}
