#pragma once

#include <ostream>

namespace minji
{
	class answer
	{
	public:
		virtual ~answer() noexcept = default;
		friend std::ostream& operator<<(std::ostream& os, const minji::answer& ans)
		{ return ans.output(os); }

	private:
		virtual std::ostream& output(std::ostream&) const = 0;
	};
}
