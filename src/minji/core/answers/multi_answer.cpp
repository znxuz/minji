#include "multi_answer.h"

namespace minji
{
    multi_answer::multi_answer(
	    std::vector<std::pair<std::string, bool>> choices) :
	choices_(std::move(choices))
    {}

    bool multi_answer::operator==(const multi_answer& ans) const
    {
	return this->choices_ == ans.choices_;
    }

    std::string multi_answer::output(reveal reveal) const
    {
	std::string output;
	for (size_t i = 0; i < choices_.size(); ++i)
	    output += std::string("- [") +
		(reveal == reveal::yes ? (choices_[i].second ?
					  "O" : "X") : "*") + "] " +
		choices_[i].first +
		(i + i == choices_.size() ? "" : "\n");

	return output;
    }

    multi_answer* multi_answer::clone_impl() const
    {
	return new multi_answer(choices_);
    }
}
