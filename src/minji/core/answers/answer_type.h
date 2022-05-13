#pragma once

#include <algorithm>
#include <array>
#include <iostream>

namespace minji
{
    enum class answer_type
    {
	plain = 'p', multiple_choice = 'm' //, word_fill
    };

    constexpr static std::array<answer_type, 2> ans_types
    {
	answer_type::plain, answer_type::multiple_choice
    };

    inline std::istream& operator>>(std::istream& is, answer_type& ans_type)
    {
	size_t in;
	is >> in;
	ans_type = static_cast<answer_type>(in);
	if (std::find(begin(ans_types), end(ans_types), ans_type) == ans_types.end())
	    is.setstate(std::ios::failbit);
	return is;
    }

    inline std::ostream& operator<<(std::ostream& os, const answer_type& ans_type)
    {
	switch (ans_type) {
	    case answer_type::plain:
		return (os << "plain");
	    case answer_type::multiple_choice:
		return (os << "multiple choice");
	}
	return os;
    }

}
