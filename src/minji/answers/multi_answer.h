#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "answer.h"

namespace minji
{
    class multi_answer : public answer
    {
	public:
	    explicit multi_answer(std::vector<std::pair<std::string, bool>> choices);
	    bool operator==(const multi_answer&) const;
	    std::string output(reveal) const override;

	private:
	    std::vector<std::pair<std::string, bool>> choices_;

	    multi_answer* clone_impl() const override;
    };
}
