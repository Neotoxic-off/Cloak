#pragma once

#include <iostream>
#include <Windows.h>
#include <minhook.h>
#include <format>
#include <sstream>

#include "logger.h"

#include "constants/logs.h"
#include "game/module.h"

bool BuildHook(Module* module, int offset, LPVOID, LPVOID*);
bool IsValidMemory(uintptr_t address);
bool ValidateOffset(HMODULE module, int offset);
bool RemoveHook(Module* module, int offset);