#include "pch.h"
#include "game/cheat.h"

int __stdcall ForceZero()
{
	Log(LOG_SUCCESS, "Forced zero");

    return 0;
}

bool __stdcall ForceTrue()
{
    Log(LOG_SUCCESS, "Forced true");

    return true;
}

bool __stdcall ForceFalse()
{
    Log(LOG_SUCCESS, "Forced false");

    return false;
}

typedef void(__fastcall* SetIsOpen_t)(void* _this, float angle);
SetIsOpen_t oSetIsOpen = nullptr;

void __fastcall SetIsOpen(void* _this, float angle)
{
    Log(LOG_SUCCESS, "Forcing isOpen to ange");
    oSetIsOpen(_this, 90.0f);
}

Cheat::Cheat()
{
	this->Assemly = (uintptr_t)GetModuleHandle(L"GameAssembly.dll");
}

void Cheat::ForceUsername()
{
	//MH_CreateHook((LPVOID*)(this->Assemly + 0x1456E00), &OnKick, NULL);
}

void Cheat::ForceBasementUnlocked()
{
    Log(LOG_WAIT, "Forcing basement unlock");

    typedef bool(*OriginalFunc)();
    OriginalFunc oTargetFunction = nullptr;

    BuildHook(this->Assemly, 0x1ae6310, &ForceTrue, nullptr);
    BuildHook(this->Assemly, 0x1ae4d80, &ForceTrue, nullptr);
    BuildHook(this->Assemly, 0x1484920, &ForceTrue, nullptr);

	Log(LOG_SUCCESS, "Forced basement unlock");
}

void Cheat::ForceNeverDead()
{
    Log(LOG_WAIT, "Forcing never dead");

    typedef bool(*OriginalFunc)();
    OriginalFunc oTargetFunction = nullptr;

    BuildHook(this->Assemly, 0xA33E80, &ForceFalse, nullptr);
    BuildHook(this->Assemly, 0xDCDDC0, &ForceFalse, nullptr);
    BuildHook(this->Assemly, 0x189DDD0, &ForceFalse, nullptr);
    BuildHook(this->Assemly, 0x189DC50, &ForceFalse, nullptr);
    BuildHook(this->Assemly, 0xA37A50, &ForceFalse, nullptr);
    BuildHook(this->Assemly, 0x52ADC0, &ForceFalse, nullptr);
    BuildHook(this->Assemly, 0x189D290, &ForceFalse, nullptr);

    Log(LOG_SUCCESS, "Forced never dead");
}

void Cheat::ForceBasementNoKeys()
{
    Log(LOG_WAIT, "Forcing basement no keys");

    typedef int(*OriginalFunc)();
    OriginalFunc oTargetFunction = nullptr;

    //BuildHook(this->Assemly, 0x1AE6910, &ForceZero, nullptr);
    //BuildHook(this->Assemly, 0x1ad13b0, &ForceZero, nullptr);
    //BuildHook(this->Assemly, 0x1ae6320, &ForceZero, nullptr);
    //BuildHook(this->Assemly, 0x1ae4d90, &ForceZero, nullptr);

	Log(LOG_SUCCESS, "Forced basement no keys");
}

void Cheat::UnlockAllDoors()
{
    Log(LOG_WAIT, "Unlocking all doors");

    //BuildHook(this->Assemly, 0x1D198F0, &SetIsOpen, nullptr);
    //BuildHook(this->Assemly, 0x1D16C40, &SetIsOpen, nullptr);

    Log(LOG_SUCCESS, "Unlocked all doors");
}

void Cheat::ForceHost()
{
    Log(LOG_WAIT, "Forcing host");

    //typedef bool(*__fastcall SetMasterClient)(LPVOID player);
    //typedef LPVOID(*__fastcall get_LocalPhotonPlayer)();

    //LPVOID localPlayer = ((get_LocalPhotonPlayer)(this->Assemly + 0x38B6380))();
    //((SetMasterClient)(this->Assemly + 0x389E970))(localPlayer);

    Log(LOG_SUCCESS, "Forced host");
}

Cheat::~Cheat()
{
}
