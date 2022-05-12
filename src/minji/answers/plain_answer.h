#pragma once

#include <iostream>
#include <string>

#include "answer.h"

namespace minji
{
    class plain_answer : public answer
    {
	public:
	    explicit plain_answer(std::string) noexcept;
	    bool operator==(const plain_answer&) const;

	private:
	    std::string ans_;

	    std::ostream& output(std::ostream&) const override;
	    plain_answer* clone_impl() const override;
    };
}
