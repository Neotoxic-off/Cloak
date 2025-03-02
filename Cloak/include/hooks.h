#pragma once

#include <iostream>
#include <Windows.h>
#include <MinHook.h>
#include <format>
#include <sstream>
#include "logger.h"

void BuildHook(uintptr_t, int, LPVOID, LPVOID*);
