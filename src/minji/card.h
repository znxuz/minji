#pragma once

#include <iostream>
#include <memory>

#include "answer.h"

namespace minji
{
	class card
	{
	public:
		card(std::string, std::unique_ptr<answer>&&, std::string category = "default");
		std::string& front();
		const std::string& front() const;
		answer& back();
		const answer& back() const;
		bool operator==(const card&) const;

	private:
		std::string _front;
		std::unique_ptr<answer> _ans;
		std::string _category;
	};

	std::ostream& operator<<(std::ostream&, const minji::card&);
}
