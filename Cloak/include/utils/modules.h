#pragma once

#include <Windows.h>

#include "game/module.h"

static Module MODULE_GAME_ASSEMBLY = Module("GameAssembly.dll", L"GameAssembly.dll");
static Module MODULE_MONO = Module("mono-2.0-bdwgc.dll", L"mono-2.0-bdwgc.dll");
