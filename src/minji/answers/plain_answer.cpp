#include "plain_answer.h"

namespace minji
{
    plain_answer::plain_answer(std::string ans) noexcept : ans_(std::move(ans))
    {}

    bool plain_answer::operator==(const plain_answer& pa) const
    {
	return this == &pa || this->ans_ == pa.ans_;
    }

    std::string plain_answer::output(reveal reveal) const
    {
	return (reveal == reveal::yes ? this->ans_ : "****");
    }

    plain_answer* plain_answer::clone_impl() const
    {
	return new plain_answer(this->ans_);
    }
}
