#include "pch.h"

#include "utils/logger.h"

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

    DisplayHeader();
    DisplayKeysMenu();
}

std::string GetKeyName(int virtualKey)
{
    UINT scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);
    char keyName[128] = { 0 };

    if (GetKeyNameTextA(scanCode << 16, keyName, sizeof(keyName))) {
        return std::string(keyName);
    }

    return "Unknown Key";
}

void Logger::DisplayKeysMenu()
{
    for (const auto& [key, description] : KEYS_MENU) {
        Log(LOG_INFO, std::format("[{}] {}", GetKeyName(key), description).c_str());
    }
}

void Logger::DisplayHeader()
{
    std::string header = HEADER;
    std::istringstream stream(header);
    std::string line;

    while (std::getline(stream, line)) {
        Log(LOG_INFO, line.c_str());
    }
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

    oss << std::put_time(&timeInfo, "%H:%M:%S");

    return oss.str();
}

void Log(const char* logType, const char* message)
{
    static std::unordered_map<std::string, int> logColors = {
        {LOG_INFO, 14},    // Yellow
        {LOG_ERROR, 12},   // Red
        {LOG_SUCCESS, 10}, // Green
        {LOG_WAIT, 13}     // Pink
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
