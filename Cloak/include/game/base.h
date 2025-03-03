#pragma once

#include "minhook.h"
#include "logger.h"

#include "utils/settings.h"

int __stdcall ForceZero();
bool __stdcall ForceTrue();
bool __stdcall ForceFalse();
int __stdcall ForceOne();
void __stdcall ForceBypass();
