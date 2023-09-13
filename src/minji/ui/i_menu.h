#pragma once

#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

#include "../core/answers/answer_factory.h"
#include "../core/answers/answer_type.h"
#include "../core/collection.h"
#include "../core/deck.h"
#include "../io/export_markdown.h"
#include "../io/parse_markdown.h"
#include "../practice/practice.h"
#include "../practice/practice_opt.h"
#include "../utils/utils.h"
#include "menu_opt.h"

namespace ui
{
    void i_menu(minji::collection& clt);
}
