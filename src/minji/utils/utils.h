#pragma once

#include <sstream>
#include <cstdlib>
#include <limits>
#include <iostream>
#include <string_view>

namespace utils
{
    constexpr static std::string_view invalid_input = "[Error] invalid input,"
	"try again\n";
    constexpr static std::string_view prompt = "  > ";

    inline const auto non_validation = [](auto) { return false; };

    inline auto& flush()
    {
	return std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    template<typename T, typename V> bool parse_input(T& t, const V& invalid)
    {
	std::cout << prompt;
	while (!(std::cin >> t) || invalid(t)) {
	    if (std::cin.eof())
		return false;
	    std::cerr << invalid_input;
	    std::cin.clear();
	    flush();
	    std::cout << prompt;
	}
	flush();

	return true;
    }

    template<typename T> bool parse_input(T& t)
    {
	return parse_input(t, non_validation);
    }

    template<typename T, typename V> bool parse_input_return_empty(T& t,
	    const V& invalid)
    {
	std::string in;
	T buf;
	std::cout << prompt;
	while (std::getline(std::cin, in) && !in.empty() &&
		(!(std::stringstream(in) >> buf) || invalid(buf))) {
	    std::cerr << invalid_input;
	    std::cout << prompt;
	}
	if (!in.empty())
	    t = std::move(buf);

	return !std::cin.eof() && !in.empty();
    }

    template <typename T> inline bool parse_input_return_empty(T& t)
    {
	return parse_input_return_empty(t, non_validation);
    }

    inline void clear_screen()
    {
	std::system("clear");
    }

    inline void prompt_enter()
    {
	std::cout << "press Enter to continue...\n";
	utils::flush();
    }

}
