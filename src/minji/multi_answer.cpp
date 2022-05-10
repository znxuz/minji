#include "multi_answer.h"

#include <iostream>

namespace minji
{
    multi_answer::multi_answer(std::vector<std::pair<std::string, bool>> choices) :
	_choices(choices)
    {}

    bool multi_answer::operator==(const multi_answer& ans) const
    {
	return this->_choices == ans._choices;
    }

    std::ostream& multi_answer::output(std::ostream& os) const
    {
	for (size_t i = 0; i < _choices.size(); ++i)
	    os << "- " << _choices[i].first <<
		"\n  -> " << std::boolalpha << _choices[i].second <<
		(i + 1 == _choices.size() ? "" : "\n");
	return os;
    }

    multi_answer* multi_answer::clone_impl() const
    {
	return new multi_answer(_choices);
    }
}
