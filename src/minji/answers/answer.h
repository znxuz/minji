#pragma once

#include <memory>
#include <ostream>

namespace minji
{
    class answer
    {
	public:
	    std::unique_ptr<answer> clone() const
	    {
		return std::unique_ptr<answer>(this->clone_impl());
	    }
	    virtual ~answer() = default;
	    friend std::ostream& operator<<(std::ostream& os,
		    const minji::answer& ans)
	    {
		return ans.output(os);
	    }

	private:
	    virtual answer* clone_impl() const = 0;
	    virtual std::ostream& output(std::ostream&) const = 0;
    };
}
