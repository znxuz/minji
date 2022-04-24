#pragma once

#include <limits>
#include <iostream>
#include <vector>
#include <memory>

#include "../minji/category.h"

namespace minji
{
	constexpr static std::string_view invalid_input = "[Error] invalid input, try again\n";
	constexpr static std::string_view prompt = "  > ";

	inline auto default_parse_validate = [](auto) { return false; };
	inline auto err_print = []() { std::cerr << invalid_input; };

	inline void flush()
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	template<typename T>
	bool parse_input(T& t, bool (*validate)(const T&) = default_parse_validate,
			void (*handle)() = err_print)
	{
		while (std::cout << "  > " &&
				(!(std::cin >> t) || validate(t))) {
			if (std::cin.eof())
				 return false;
			if (validate(t))
				handle();
			else
				err_print();
			flush();
		}
		flush();

		return true;
	}
}

void i_menu(std::vector<std::shared_ptr<minji::category>> categories = {});
