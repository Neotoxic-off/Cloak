#pragma once

#include <iostream>
#include <Windows.h>
#include <minhook.h>
#include <format>
#include <sstream>
#include "logger.h"

bool BuildHook(uintptr_t, int, LPVOID, LPVOID*);
