#pragma once

static const char* LOG_ERROR_OFFSET_NOT_READY = "Offset is not ready or invalid";
static const char* LOG_SUCCESS_OFFSET_READY = "Offset is ready";

static const char* LOG_WAIT_LOADING_MODULE = "Loading cheat module";
static const char* LOG_SUCCESS_LOADING_MODULE = "Loaded cheat module";
static const char* LOG_ERROR_LOADING_MODULE = "Failed cheat module";

static const char* LOG_ERROR_HOOK_CREATE_FAILED = "Failed to create hook";
static const char* LOG_ERROR_HOOK_ENABLE_FAILED = "Failed to enable hook";

static const char* LOG_WAIT_DEBUGGER_CLEARING = "Clearing PEB debugger flags";
static const char* LOG_SUCCESS_DEBUGGER_CLEARED = "PEB debugger flags cleared";

static const char* LOG_WAIT_NTSET_CLEARING = "Retrieving NtSetInformationProcess function address";
static const char* LOG_ERROR_NTSET_RETRIEVE_FAILED = "Failed to get NtSetInformationProcess function address";
static const char* LOG_SUCCESS_NTSET_RETRIEVED = "NtSetInformationProcess function address retrieved";

static const char* LOG_ERROR_NTDLL_HANDLE_FAILED = "Failed to get ntdll.dll module handle";
static const char* LOG_INFO_DISABLE_DEBUGGER = "Disabling debugger detection";
static const char* LOG_ERROR_NTSET_INFO_RETRIEVE_FAILED = "Failed to retrieve NtSetInformationProcess, skipping debugger disabling";
static const char* LOG_SUCCESS_DEBUGGER_DISABLED = "Debugger detection disabled";

static const char* LOG_WAIT_PATCHING = "Patching debugger detection";
static const char* LOG_SUCCESS_PATCHED = "Patched debugger detection";
static const char* LOG_ERROR_PEB_RETRIEVE_FAILED = "Failed to retrieve PEB address";

static const char* LOG_WAIT_PRESENCE_PATCHING = "Patching presence";
static const char* LOG_SUCCESS_PRESENCE_PATCHED = "Patched presence";

static const char* LOG_WAIT_PROCESS_LOADING = "Waiting process loading";
static const char* LOG_SUCCESS_PROCESS_LOADING = "Process waited";

static const char* LOG_INFO_BYPASSING_BREAKPOINTS = "Bypassing breakpoint detection...";
static const char* LOG_INFO_BYPASSING_ANTI_DEBUG = "Bypassing anti-debugging techniques...";
static const char* LOG_INFO_NEUTRALIZING_TIMING_CHECKS = "Neutralizing timing checks...";
static const char* LOG_INFO_NEUTRALIZING_EXCEPTIONS = "Neutralizing exception handlers...";
static const char* LOG_INFO_RESTORING_HOOKS = "Restoring hooked APIs...";

static const char* LOG_INFO_ALLOWING_MEMORY_ACCESS = "Allowing memory queries...";

static const char* LOG_SUCCESS_MEMORY_QUERY_BYPASSED = "Memory query protection bypassed";
static const char* LOG_ERROR_MEMORY_PROTECTION_FAILED = "Failed to modify memory protection";
static const char* LOG_ERROR_NTQUERYVIRTUALMEMORY_FAILED = "Failed to locate NtQueryVirtualMemory";

static const char* LOG_SUCCESS_SYSTEM_QUERY_BYPASSED = "System information query protection bypassed";
static const char* LOG_ERROR_SYSTEM_QUERY_PATCH_FAILED = "Failed to modify system query protection";
static const char* LOG_ERROR_NTQUERYSYSTEMINFORMATION_FAILED = "Failed to locate NtQuerySystemInformation";
