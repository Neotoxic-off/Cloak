#include "pch.h"
#include "game/attribute.h"

Attribute::Attribute()
{
	this->Assemly = (uintptr_t)GetModuleHandle((LPCWSTR)"Assembly-CSharp.dll");
}

void Attribute::ForceUsername()
{
	//MH_CreateHook((LPVOID*)(this->Assemly + 0x14589F0), &hkSetFunction, (LPVOID*)&oSetFunction);
	//MH_CreateHook((LPVOID*)(this->Assemly + 0x1456E00), &OnKick, NULL);
}

Attribute::~Attribute()
{
}
