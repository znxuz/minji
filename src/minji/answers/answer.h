#pragma once

#include <memory>
#include <ostream>

namespace minji
{
    class answer
    {
	public:
	    enum class reveal { yes, no };

	    std::unique_ptr<answer> clone() const
	    {
		return std::unique_ptr<answer>(this->clone_impl());
	    }
	    friend std::ostream& operator<<(std::ostream& os,
		    const minji::answer& ans)
	    {
		return (os << ans.output(reveal::yes));
	    }
	    virtual ~answer() = default;
	    virtual std::string output(reveal) const = 0;

	private:
	    virtual answer* clone_impl() const = 0;
    };
}
