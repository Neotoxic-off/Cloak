#pragma once

#include <iostream>
#include <stdio.h>
#include <format>
#include <windows.h>
#include <tlhelp32.h>

#define LOG_WAIT "WAIT"
#define LOG_SUCCESS "DONE"
#define LOG_ERROR "ERRO"

class Logger {
	private:
		void Load();
		void Unload();

	public:
		void Log(const char*, const char*);

		Logger();
		~Logger();
};
