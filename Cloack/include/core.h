#pragma once

#include <iostream>
#include <stdio.h>
#include <format>
#include <windows.h>
#include <tlhelp32.h>

#include "pch.h"
#include "logger.h"
#include "modules/peb.h"
#include "modules/presence.h"

class Core
{
	private:
		Logger logger;

		Presence presence;
		PEB peb;

		void Load();
		void Unload();
	
	public:
		Core();
		~Core();

		void ApplySecurityModules();
		void HidePresence();
		void PatchPEB();
};
