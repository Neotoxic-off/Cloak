#pragma once

#define LOG_WAIT_OFFSET_READY "Checking if offset is ready"
#define LOG_SUCCESS_OFFSET_READY "Offset is ready"
#define LOG_ERROR_OFFSET_NOT_READY "Offset is not ready or invalid"

#define LOG_WAIT_LOADING_MODULE "Loading cheat module"
#define LOG_SUCCESS_LOADING_MODULE "Loaded cheat module"
#define LOG_ERROR_LOADING_MODULE "Failed to load cheat module"

#define LOG_WAIT_HOOK_CREATION "Creating hook"
#define LOG_SUCCESS_HOOK_CREATED "Hook created"
#define LOG_ERROR_HOOK_CREATE_FAILED "Failed to create hook"

#define LOG_WAIT_HOOK_ENABLING "Enabling hook"
#define LOG_SUCCESS_HOOK_ENABLED "Hook enabled"
#define LOG_ERROR_HOOK_ENABLE_FAILED "Failed to enable hook"

#define LOG_WAIT_DEBUGGER_CLEARING "Clearing PEB debugger flags"
#define LOG_SUCCESS_DEBUGGER_CLEARED "PEB debugger flags cleared"
#define LOG_ERROR_DEBUGGER_CLEAR_FAILED "Failed to clear PEB debugger flags"

#define LOG_WAIT_NTSET_CLEARING "Retrieving NtSetInformationProcess function address"
#define LOG_SUCCESS_NTSET_CLEARED "NtSetInformationProcess function address retrieved"
#define LOG_ERROR_NTSET_CLEAR "Failed to get NtSetInformationProcess function address"

#define LOG_WAIT_NTDLL_HANDLE "Retrieving ntdll.dll module handle"
#define LOG_SUCCESS_NTDLL_HANDLE "ntdll.dll module handle retrieved"
#define LOG_ERROR_NTDLL_HANDLE_FAILED "Failed to get ntdll.dll module handle"

#define LOG_WAIT_DEBUGGER_DISABLING "Disabling debugger detection"
#define LOG_SUCCESS_DEBUGGER_DISABLED "Debugger detection disabled"
#define LOG_ERROR_NTSET_INFO_RETRIEVE_FAILED "Failed to retrieve NtSetInformationProcess, skipping debugger disabling"

#define LOG_WAIT_PATCHING "Patching debugger detection"
#define LOG_SUCCESS_PATCHED "Patched debugger detection"
#define LOG_ERROR_PATCHING_FAILED "Failed to patch debugger detection"

#define LOG_WAIT_PRESENCE_PATCHING "Patching presence"
#define LOG_SUCCESS_PRESENCE_PATCHED "Patched presence"
#define LOG_ERROR_PRESENCE_PATCH_FAILED "Failed to patch presence"

#define LOG_WAIT_PROCESS_LOADING "Waiting for process to load"
#define LOG_SUCCESS_PROCESS_LOADED "Process loaded"
#define LOG_ERROR_PROCESS_LOAD_FAILED "Failed to load process"

#define LOG_WAIT_MEMORY_ACCESS "Allowing memory queries"
#define LOG_SUCCESS_MEMORY_QUERY_BYPASSED "Memory query protection bypassed"
#define LOG_ERROR_MEMORY_PROTECTION_FAILED "Failed to modify memory protection"
#define LOG_ERROR_NTQUERYVIRTUALMEMORY_FAILED "Failed to locate NtQueryVirtualMemory"

#define LOG_WAIT_SYSTEM_QUERY_PATCH "Patching system information query protection"
#define LOG_SUCCESS_SYSTEM_QUERY_BYPASSED "System information query protection bypassed"
#define LOG_ERROR_SYSTEM_QUERY_PATCH_FAILED "Failed to modify system query protection"
#define LOG_ERROR_NTQUERYSYSTEMINFORMATION_FAILED "Failed to locate NtQuerySystemInformation"

#define LOG_WAIT_BUILD_MODULES "Building modules"
#define LOG_SUCCESS_BUILD_MODULES "Built modules"
#define LOG_ERROR_BUILD_MODULES "Failed to build modules"

#define LOG_WAIT_HOOKING_CHEATS "Hooking cheats"
#define LOG_SUCCESS_HOOKING_CHEATS "Hooked cheats"
#define LOG_ERROR_HOOKING_CHEATS "Failed hooking cheats"

#define LOG_WAIT_UNHOOKING_CHEATS "Unhooking cheats"
#define LOG_SUCCESS_UNHOOKING_CHEATS "Unhooked cheats"
#define LOG_ERROR_UNHOOKING_CHEATS "Failed unhooking cheats"

#define LOG_WAIT_HOOKING_CHEAT "Hooking cheat"
#define LOG_SUCCESS_HOOKING_CHEAT "Hooked cheat"
#define LOG_ERROR_HOOKING_CHEAT "Failed hooking cheat"

#define LOG_ERROR_HOOK_REMOVING_FAILED "Failed removing cheat"
#define LOG_ERROR_HOOK_DISABLING_FAILED "Failed disabling cheat"

#define LOG_WAIT_UNHOOKING_CHEAT "Uncooking cheat"
#define LOG_SUCCESS_UNHOOKING_CHEAT "Unhooked cheat"
#define LOG_ERROR_UNHOOKING_CHEAT "Failed unhooking cheat"

#define LOG_WAIT_BUILDING_MODULE "Building module"
#define LOG_SUCCESS_BUILDING_MODULE "Built module"
#define LOG_ERROR_BUILDING_MODULE "Failed building module"

#define LOG_WAIT_INFORMATION_MODULE "Loading module information"
#define LOG_SUCCESS_INFORMATION_MODULE "Loaded module information"

#define LOG_SUCCESS_SEARCHING_PATTERN "Pattern found"
#define LOG_ERROR_SEARCHING_PATTERN "Pattern not found"
