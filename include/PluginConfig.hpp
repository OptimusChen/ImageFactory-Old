#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "main.hpp"

//#include "beatsaber-hook/shared/config/config-utils.hpp"
#include "config-utils/shared/config-utils.hpp"
using namespace std;

DECLARE_CONFIG(PluginConfig,
               CONFIG_VALUE(Images, std::string, "Saved Images", "");
               CONFIG_VALUE(Amount, int, "Images", 0);
               CONFIG_INIT_FUNCTION(CONFIG_INIT_VALUE(Images);
                                    CONFIG_INIT_VALUE(Amount);))