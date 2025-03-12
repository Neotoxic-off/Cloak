
#pragma once

#include <windows.h>
#include <format>
#include <map>

#define VERSION "0.3.0"
#define HEADER R"(

             .,ad88888ba,.
         .,ad8888888888888a,
        d8P"""98888P"""98888b,
        9b    d8888,    `9888B
      ,d88aaa8888888b,,,d888P'
     d8888888888888888888888b
    d888888P""98888888888888P
    88888P'    9888888888888
    `98P'       9888888888P'
                 `"9888P"'
                    `"'

)"


static const int WAIT_PROCESS_LOADING_TIME = 2000;
static const int WAIT_KEY_INPUT_TIME = 100;

static const int KEY_REHOOK_CHEAT_MODULES = VK_F1;
static const int KEY_SCAN_PATTERNS = VK_F2;
static const int KEY_UNLOAD = VK_F4;

static const std::map<int, std::string> KEYS_MENU = {
    {KEY_REHOOK_CHEAT_MODULES, "Rehook cheat modules"},
    {KEY_SCAN_PATTERNS, "Scan patterns"},
    {KEY_UNLOAD, "Unloads dll"}
};
