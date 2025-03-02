#pragma once

#include <windows.h>
#include <tlhelp32.h>
#include "logger.h"

class PEB
{
	public:
		PEB();
		~PEB();

		void Patch();
};
