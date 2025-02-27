#include "pch.h"
#include "logger.h"

Logger::Logger() {
    Load();
}

Logger::~Logger() {
	Unload();
}

void Logger::Load() {
    FILE* fDummy;

    AllocConsole();
    //SetConsoleTitleA("Cloak");

    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONIN$", "r", stdin);
}

void Logger::Log(const char* logType, const char* message) {
    std::cout << std::format("[{}] {}", logType, message) << std::endl;
}

void Logger::Unload() {
    FreeConsole();
}
