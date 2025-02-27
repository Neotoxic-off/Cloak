#pragma once

#include <windows.h>
#include <tlhelp32.h>

class PEB
{
	public:
		PEB();
		~PEB();

		void Patch();
};
