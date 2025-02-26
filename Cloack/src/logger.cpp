#include "pch.h"
#include "logger.h"

Logger::Logger() {
    Load();
}

Logger::~Logger() {
	Unload();
}

void Logger::Load() {
    AllocConsole();

    FILE* fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONIN$", "r", stdin);
}

void Logger::Log(const char* logType, const char* message) {
    char timeStr[9];
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm local_time;
    localtime_s(&local_time, &now_time);

    std::strftime(timeStr, sizeof(timeStr), "%X", &local_time);

    std::cout << std::format("{} | {} {}", timeStr, logType, message) << std::endl;
}

void Logger::Unload() {
    FreeConsole();
}
