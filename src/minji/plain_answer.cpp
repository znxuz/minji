#include "plain_answer.h"

namespace minji
{
	plain_answer::plain_answer(std::string ans) noexcept : _ans(std::move(ans))
	{ }

	std::ostream& plain_answer::output(std::ostream& os) const
	{
		return (os << this->_ans);
	}

	std::ostream& operator<<(std::ostream& os, const minji::plain_answer& pa)
	{
		return pa.output(os);
	}
}
