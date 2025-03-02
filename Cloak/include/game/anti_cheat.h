#pragma once

#include <windows.h>
#include <iostream>
#include "MinHook.h"
#include "logger.h"
#include "hooks.h"

void DullStart();

class AntiCheat
{
	private:
		uintptr_t Assemly;


	public:
		AntiCheat();
		~AntiCheat();

		void NoStart();
};
