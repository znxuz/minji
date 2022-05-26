#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>
#include <string_view>

#include "../core/deck.h"
#include "../utils/utils.h"

namespace io
{
    void export_markdown(const minji::deck* deck);
}
