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

    /*
    template<typename T, typename V> bool parse_input_ignore_newline(T& t, const V& invalid)
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

    template<typename T> bool parse_input_ignore_newline(T& t)
    {
	return parse_input_ignore_newline(t, non_validation);
    }
    */

    template<typename T, typename V> bool parse_input(T& t,
	    const V& invalid)
    {
	T buf;
	std::string in;

	std::cout << prompt;
	while (std::getline(std::cin, in) && !in.empty()) {
	    std::istringstream iss(in);
	    if ((iss >> buf) && (iss.eof() ||
			iss.peek() == std::char_traits<char>::eof()) &&
		    !invalid(buf))
		break;
	    std::cerr << invalid_input;
	    std::cout << prompt;
	}

	if (in.empty())
	    return false;
	t = std::move(buf);
	return !std::cin.eof();
    }

    template <typename T> inline bool parse_input(T& t)
    {
	return parse_input(t, non_validation);
    }

    inline bool parse_input_getline(std::string& s)
    {
	return std::cout << prompt && std::getline(std::cin, s) && !s.empty();
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
