#pragma once

#include "minhook.h"
#include "utils/logger.h"

int __stdcall DummyZero();
bool __stdcall DummyTrue();
bool __stdcall DummyFalse();
int __stdcall DummyOne();
void __stdcall DummySkip();
