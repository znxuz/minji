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

    inline void flush()
    {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    template<typename T, typename V> bool parse_input(T& t, const V& v)
    {
	std::cout << prompt;
	while (!(std::cin >> t) || v(t)) {
	    if (std::cin.eof())
		return false;
	    std::cerr << invalid_input;
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

    template<typename T, typename V> bool parse_input_allow_empty(T& t,
	    const V& v)
    {
	std::cout << prompt;
	std::string line;
	T buf;
	while (std::getline(std::cin, line) && !line.empty()) {
	    std::stringstream ss(line);
	    if ((ss >> buf) && !v(buf))
		break;
	    // FIXME t garbage value
	    std::cerr << invalid_input;
	    std::cout << prompt;
	}

	if (!line.empty())
	    t = std::move(buf);
	return !std::cin.eof();
    }

    template <typename T> inline bool parse_input_allow_empty(T& t)
    {
	return parse_input_allow_empty(t, non_validation);
    }

    inline void clear_screen()
    {
	std::system("clear");
    }
}
