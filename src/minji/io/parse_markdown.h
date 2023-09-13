#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <regex>
#include <string>

#include "../core/answers/answer_factory.h"
#include "../core/answers/multi_answer.h"
#include "../core/answers/plain_answer.h"
#include "../core/card.h"
#include "../core/deck.h"
#include "parse_error.h"

namespace io
{
    std::shared_ptr<minji::deck> parse_markdown(const std::filesystem::path& p,
        const std::string& deck_name);
}
