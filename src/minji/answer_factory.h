#pragma once

#include <string>
#include <vector>

#include <iostream>
#include "answer.h"
#include "card.h"
#include "plain_answer.h"
#include "answer_type.h"

namespace minji
{
	std::unique_ptr<answer> make_answer(std::string plain);
	std::unique_ptr<answer> make_answer(std::vector<std::string> choices,
			std::vector<int> correct_indices);
}

