#pragma once

#include <iostream>
#include <stdio.h>
#include <format>
#include <windows.h>
#include <tlhelp32.h>

#define LOG_WAIT "*"
#define LOG_SUCCESS "+"
#define LOG_ERROR "x"

void Log(const char*, const char*);

class Logger {
	private:
		void Load();
		void Unload();

	public:

		Logger();
		~Logger();
};
