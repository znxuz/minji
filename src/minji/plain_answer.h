#pragma once

#include <iostream>
#include <string>

#include "answer.h"

namespace minji
{
	class plain_answer : public answer
	{
	public:
		plain_answer(std::string) noexcept;

		friend std::ostream& operator<<(std::ostream&, const plain_answer&);

	private:
		std::string _ans;

		std::ostream& output(std::ostream&) const override;
	};
}
