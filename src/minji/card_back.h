# pragma once

#include <string>
#include <memory>

namespace minji
{
	class card_back
	{
	public:
		card_back() = default;
		card_back(const card_back&) = default;
		card_back(card_back&&) = default;
		card_back& operator=(const card_back&) = default;
		card_back& operator=(card_back&&) = default;
		virtual ~card_back() = default;
		friend std::ostream& operator<<(std::ostream& os, const minji::card_back& ans);

	private:
	};
}
