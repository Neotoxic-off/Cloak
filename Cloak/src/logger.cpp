#include "pch.h"
#include "logger.h"

Logger::Logger()
{
    Load();
}

Logger::~Logger()
{
    Unload();
}

void Logger::Load()
{
    FILE* fDummy;

    AllocConsole();
    SetConsoleTitleA(std::format("Cloak v{}", VERSION).c_str());

    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONIN$", "r", stdin);
}

void SetConsoleColor(int textColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor);
}

std::string GetTime()
{
    std::tm timeInfo;
    std::ostringstream oss;
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    localtime_s(&timeInfo, &now_time);

    oss << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S");

    return oss.str();
}

void Log(const char* logType, const char* message)
{
    static std::unordered_map<std::string, int> logColors = {
        {LOG_INFO, 9},
        {LOG_ERROR, 12},
        {LOG_SUCCESS, 10},
        {LOG_WAIT, 14}
    };

    int color = logColors[logType];

    std::string timeStr = GetTime();

    SetConsoleColor(8);
    std::cout << timeStr << " ";

    SetConsoleColor(color);
    std::cout << std::format("[{}]", logType);

    SetConsoleColor(7);
    std::cout << " " << message << std::endl;
}

void Logger::Unload()
{
    FreeConsole();
}
