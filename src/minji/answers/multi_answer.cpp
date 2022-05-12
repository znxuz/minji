#include "multi_answer.h"

namespace minji
{
    multi_answer::multi_answer(std::vector<std::pair<std::string, bool>> choices) :
	choices_(choices)
    {}

    bool multi_answer::operator==(const multi_answer& ans) const
    {
	return this->choices_ == ans.choices_;
    }

    std::ostream& multi_answer::output(std::ostream& os) const
    {
	for (size_t i = 0; i < choices_.size(); ++i)
	    os << "- " << choices_[i].first <<
		"\n  -> " << std::boolalpha << choices_[i].second <<
		(i + 1 == choices_.size() ? "" : "\n");
	return os;
    }

    multi_answer* multi_answer::clone_impl() const
    {
	return new multi_answer(choices_);
    }
}
