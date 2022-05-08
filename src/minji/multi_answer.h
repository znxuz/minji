#pragma once

#include <vector>
#include <string>

#include "answer.h"

namespace minji
{
    class multi_answer : public answer
    {
	public:
	    multi_answer(std::vector<std::pair<std::string, bool>> choices);
	    bool operator==(const multi_answer&) const;

	private:
	    std::vector<std::pair<std::string, bool>> _choices;

	    std::ostream& output(std::ostream&) const override;
	    multi_answer* clone_impl() const override;
    };
}
