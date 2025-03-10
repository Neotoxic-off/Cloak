
#pragma once

#include <windows.h>
#include <format>
#include <map>

#define VERSION "0.3.0"
#define HEADER R"(


O       o O       o O       o O       o O       o O       o
| O   o | | O   o | | O   o | | O   o | | O   o | | O   o |
| | O | | | | O | | | | O | | | | O | | | | O | | | | O | |
| o   O | | o   O | | o   O | | o   O | | o   O | | o   O |
o       O o       O o       O o       O o       O o       O


)"


static const int WAIT_PROCESS_LOADING_TIME = 2000;
static const int WAIT_KEY_INPUT_TIME = 100;

static const int KEY_REHOOK_CHEAT_MODULES = VK_F1;
static const int KEY_UNLOAD = VK_F4;

static const std::map<int, std::string> KEYS_MENU = {
    {KEY_REHOOK_CHEAT_MODULES, "Rehook cheat modules"},

    {KEY_UNLOAD, "Unloads dll"}
};
