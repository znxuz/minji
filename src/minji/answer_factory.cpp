#include "answer_factory.h"
#include <memory>
#include <stdexcept>

namespace minji
{
	std::unique_ptr<answer> make_answer(std::string plain)
	{
		return std::unique_ptr<answer>(std::make_unique<plain_answer>(plain));
	}

	std::unique_ptr<answer> make_answer(std::vector<std::string> choices,
			std::vector<int> correct_indices)
	{
		// TODO multi answer
		return {};
	}
}
