#pragma once

#include <limits>
#include <iostream>
#include <vector>
#include <memory>

#include "../minji/category.h"

void interactive_menu(std::vector<std::shared_ptr<minji::category>> categories = {});
