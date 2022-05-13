#include "answer_factory.h"

namespace minji
{
    std::unique_ptr<answer> make_answer(std::string plain)
    {
	return std::make_unique<plain_answer>(plain);
    }

    std::unique_ptr<answer> make_answer(std::vector<std::pair<std::string, bool>> choices)
    {
	return std::make_unique<multi_answer>(std::move(choices));
    }
}
