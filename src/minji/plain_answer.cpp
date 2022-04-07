#include "plain_answer.h"

namespace minji
{
	plain_answer::plain_answer(std::string ans) noexcept : _ans(std::move(ans))
	{ }

	bool plain_answer::operator==(const plain_answer& pa) const
	{
		return this == &pa || this->_ans == pa._ans;
	}

	std::ostream& plain_answer::output(std::ostream& os) const
	{
		return (os << this->_ans);
	}
}
