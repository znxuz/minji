#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "answer.h"
#include "answer_type.h"
#include "plain_answer.h"
#include "multi_answer.h"


namespace minji
{
    std::unique_ptr<answer> make_answer(std::string plain);
    std::unique_ptr<answer> make_answer(std::vector<std::pair<std::string, bool>> choices);
}
