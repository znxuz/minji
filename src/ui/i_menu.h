#pragma once

#include <limits>
#include <iostream>
#include <vector>
#include <memory>

#include "../minji/deck.h"

namespace minji
{
    constexpr static std::string_view invalid_input = "[Error] invalid input, try again\n";
    constexpr static std::string_view prompt = "  > ";

    inline auto default_validate = [](auto) { return false; };

    inline void flush()
    {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    template<typename T, typename V>
    bool parse_input(T& t, V& v)
    {
	while (std::cout << "  > " && (!(std::cin >> t) || v(t))) {
	    if (std::cin.eof())
		return false;
	    std::cerr << invalid_input;
	    flush();
	}
	flush();

	return true;
    }

    template<typename T>
    bool parse_input(T& t)
    {
	return parse_input(t, default_validate);
    }
}

void i_menu(std::vector<std::shared_ptr<minji::deck>> decks = {});
