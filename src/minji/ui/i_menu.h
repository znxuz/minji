#pragma once

#include <limits>
#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>

#include "menu_opt.h"
#include "../core/collection.h"
#include "../core/deck.h"
#include "../core/deck.h"
#include "../core/answers/answer_type.h"
#include "../core/answers/answer_factory.h"
#include "../practice/practice_opt.h"
#include "../practice/practice.h"
#include "../utils/utils.h"
#include "../io/export_markdown.h"
#include "../io/parse_markdown.h"

namespace ui
{
    void i_menu(minji::collection& clt);
}

