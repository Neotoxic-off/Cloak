#pragma once

static const char* LOG_WAIT_OFFSET_READY = "Checking if offset is ready";
static const char* LOG_SUCCESS_OFFSET_READY = "Offset is ready";
static const char* LOG_ERROR_OFFSET_NOT_READY = "Offset is not ready or invalid";

static const char* LOG_WAIT_LOADING_MODULE = "Loading cheat module";
static const char* LOG_SUCCESS_LOADING_MODULE = "Loaded cheat module";
static const char* LOG_ERROR_LOADING_MODULE = "Failed to load cheat module";

static const char* LOG_WAIT_HOOK_CREATION = "Creating hook";
static const char* LOG_SUCCESS_HOOK_CREATED = "Hook created";
static const char* LOG_ERROR_HOOK_CREATE_FAILED = "Failed to create hook";

static const char* LOG_WAIT_HOOK_ENABLING = "Enabling hook";
static const char* LOG_SUCCESS_HOOK_ENABLED = "Hook enabled";
static const char* LOG_ERROR_HOOK_ENABLE_FAILED = "Failed to enable hook";

static const char* LOG_WAIT_DEBUGGER_CLEARING = "Clearing PEB debugger flags";
static const char* LOG_SUCCESS_DEBUGGER_CLEARED = "PEB debugger flags cleared";
static const char* LOG_ERROR_DEBUGGER_CLEAR_FAILED = "Failed to clear PEB debugger flags";

static const char* LOG_WAIT_NTSET_CLEARING = "Retrieving NtSetInformationProcess function address";
static const char* LOG_SUCCESS_NTSET_CLEARED = "NtSetInformationProcess function address retrieved";
static const char* LOG_ERROR_NTSET_CLEAR = "Failed to get NtSetInformationProcess function address";

static const char* LOG_WAIT_NTDLL_HANDLE = "Retrieving ntdll.dll module handle";
static const char* LOG_SUCCESS_NTDLL_HANDLE = "ntdll.dll module handle retrieved";
static const char* LOG_ERROR_NTDLL_HANDLE_FAILED = "Failed to get ntdll.dll module handle";

static const char* LOG_WAIT_DEBUGGER_DISABLING = "Disabling debugger detection";
static const char* LOG_SUCCESS_DEBUGGER_DISABLED = "Debugger detection disabled";
static const char* LOG_ERROR_NTSET_INFO_RETRIEVE_FAILED = "Failed to retrieve NtSetInformationProcess, skipping debugger disabling";

static const char* LOG_WAIT_PATCHING = "Patching debugger detection";
static const char* LOG_SUCCESS_PATCHED = "Patched debugger detection";
static const char* LOG_ERROR_PATCHING_FAILED = "Failed to patch debugger detection";

static const char* LOG_WAIT_PRESENCE_PATCHING = "Patching presence";
static const char* LOG_SUCCESS_PRESENCE_PATCHED = "Patched presence";
static const char* LOG_ERROR_PRESENCE_PATCH_FAILED = "Failed to patch presence";

static const char* LOG_WAIT_PROCESS_LOADING = "Waiting for process to load";
static const char* LOG_SUCCESS_PROCESS_LOADED = "Process loaded";
static const char* LOG_ERROR_PROCESS_LOAD_FAILED = "Failed to load process";

static const char* LOG_WAIT_MEMORY_ACCESS = "Allowing memory queries";
static const char* LOG_SUCCESS_MEMORY_QUERY_BYPASSED = "Memory query protection bypassed";
static const char* LOG_ERROR_MEMORY_PROTECTION_FAILED = "Failed to modify memory protection";
static const char* LOG_ERROR_NTQUERYVIRTUALMEMORY_FAILED = "Failed to locate NtQueryVirtualMemory";

static const char* LOG_WAIT_SYSTEM_QUERY_PATCH = "Patching system information query protection";
static const char* LOG_SUCCESS_SYSTEM_QUERY_BYPASSED = "System information query protection bypassed";
static const char* LOG_ERROR_SYSTEM_QUERY_PATCH_FAILED = "Failed to modify system query protection";
static const char* LOG_ERROR_NTQUERYSYSTEMINFORMATION_FAILED = "Failed to locate NtQuerySystemInformation";

static const char* LOG_WAIT_BUILD_MODULES = "Building modules";
static const char* LOG_SUCCESS_BUILD_MODULES = "Built modules";
static const char* LOG_ERROR_BUILD_MODULES = "Failed to build modules";

static const char* LOG_WAIT_HOOKING_CHEATS = "Hooking cheats";
static const char* LOG_SUCCESS_HOOKING_CHEATS = "Hooked cheats";
static const char* LOG_ERROR_HOOKING_CHEATS = "Failed hooking cheats";

static const char* LOG_WAIT_UNHOOKING_CHEATS = "Unhooking cheats";
static const char* LOG_SUCCESS_UNHOOKING_CHEATS = "Unhooked cheats";
static const char* LOG_ERROR_UNHOOKING_CHEATS = "Failed unhooking cheats";

static const char* LOG_WAIT_HOOKING_CHEAT = "Hooking cheat";
static const char* LOG_SUCCESS_HOOKING_CHEAT = "Hooked cheat";
static const char* LOG_ERROR_HOOKING_CHEAT = "Failed hooking cheat";

static const char* LOG_ERROR_HOOK_REMOVING_FAILED = "Failed removing cheat";
static const char* LOG_ERROR_HOOK_DISABLING_FAILED = "Failed disabling cheat";

static const char* LOG_WAIT_UNHOOKING_CHEAT = "Uncooking cheat";
static const char* LOG_SUCCESS_UNHOOKING_CHEAT = "Unhooked cheat";
static const char* LOG_ERROR_UNHOOKING_CHEAT = "Failed unhooking cheat";

static const char* LOG_WAIT_BUILDING_MODULE = "Building module";
static const char* LOG_SUCCESS_BUILDING_MODULE = "Built module";
static const char* LOG_ERROR_BUILDING_MODULE = "Failed building module";