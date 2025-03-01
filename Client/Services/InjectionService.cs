using System;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using Client.Utils;

namespace Client.Services
{
    public class InjectionService
    {
        public LogService? LogService { get; set; }

        public InjectionService(LogService? logService = null)
        {
            LogService = logService;
        }

        public bool InjectDll(Process targetProcess, string dllPath)
        {
            LogService?.Record(Logs.LOG_INJECTING);
            if (!ValidateInjection(targetProcess, dllPath)) return false;

            IntPtr procHandle = OpenTargetProcess(targetProcess);
            if (procHandle == IntPtr.Zero) return false;

            IntPtr loadLibraryAddr = GetLoadLibraryAddress();
            if (loadLibraryAddr == IntPtr.Zero) return false;

            IntPtr allocMemAddress = AllocateMemory(procHandle, dllPath);
            if (allocMemAddress == IntPtr.Zero) return false;

            if (!WriteMemory(procHandle, allocMemAddress, dllPath)) return false;

            bool success = CreateRemoteThread(procHandle, loadLibraryAddr, allocMemAddress);
            CleanupInjection(procHandle, allocMemAddress, success);

            LogService?.Record(success ? Logs.LOG_INJECTION_SUCCESS : Logs.LOG_INJECTION_FAILED);
            return success;
        }

        public bool EjectDll(Process targetProcess, string dllPath)
        {
            LogService?.Record(Logs.LOG_EJECTING);
            if (targetProcess == null)
            {
                LogService?.Record(Logs.LOG_EJECTION_PROCESS_NULL);
                return false;
            }

            IntPtr dllBaseAddr = GetDllBaseAddress(targetProcess, Path.GetFileName(dllPath));
            if (dllBaseAddr == IntPtr.Zero)
            {
                LogService?.Record(Logs.LOG_DLL_NOT_IN_PROCESS);
                return false;
            }

            IntPtr procHandle = OpenTargetProcess(targetProcess);
            if (procHandle == IntPtr.Zero) return false;

            bool success = UnloadDll(procHandle, dllBaseAddr);
            Utils.Kernel32.CloseHandle(procHandle);

            LogService?.Record(success ? Logs.LOG_EJECTION_SUCCESS : Logs.LOG_EJECTION_FAILED);
            return success;
        }

        private bool ValidateInjection(Process targetProcess, string dllPath)
        {
            if (targetProcess == null)
            {
                LogService?.Record(Logs.LOG_TARGET_PROCESS_NULL);
                return false;
            }

            if (!File.Exists(dllPath))
            {
                LogService?.Record(Logs.LOG_DLL_NOT_FOUND);
                return false;
            }

            return true;
        }

        private IntPtr OpenTargetProcess(Process targetProcess)
        {
            IntPtr procHandle = Utils.Kernel32.OpenProcess(
                Utils.Constants.PROCESS_CREATE_THREAD |
                Utils.Constants.PROCESS_QUERY_INFORMATION |
                Utils.Constants.PROCESS_VM_OPERATION |
                Utils.Constants.PROCESS_VM_WRITE |
                Utils.Constants.PROCESS_VM_READ,
                false,
                targetProcess.Id
            );

            if (procHandle == IntPtr.Zero)
            {
                LogService?.Record(Logs.LOG_PROCESS_OPEN_FAILED);
            }

            return procHandle;
        }

        private IntPtr GetLoadLibraryAddress()
        {
            IntPtr loadLibraryAddr = Utils.Kernel32.GetProcAddress(
                Utils.Kernel32.GetModuleHandle("kernel32.dll"),
                "LoadLibraryA"
            );

            if (loadLibraryAddr == IntPtr.Zero)
            {
                LogService?.Record(Logs.LOG_LOADLIBRARY_NOT_FOUND);
            }

            return loadLibraryAddr;
        }

        private IntPtr AllocateMemory(IntPtr procHandle, string dllPath)
        {
            IntPtr allocMemAddress = Utils.Kernel32.VirtualAllocEx(
                procHandle,
                IntPtr.Zero,
                (uint)((dllPath.Length + 1) * Marshal.SizeOf(typeof(char))),
                Utils.Constants.MEM_COMMIT | Utils.Constants.MEM_RESERVE,
                Utils.Constants.PAGE_READWRITE
            );

            if (allocMemAddress == IntPtr.Zero)
            {
                LogService?.Record(Logs.LOG_MEMORY_ALLOCATION_FAILED);
            }

            return allocMemAddress;
        }

        private bool WriteMemory(IntPtr procHandle, IntPtr allocMemAddress, string dllPath)
        {
            UIntPtr bytesWritten;
            bool success = Utils.Kernel32.WriteProcessMemory(
                procHandle,
                allocMemAddress,
                Encoding.Default.GetBytes(dllPath),
                (uint)((dllPath.Length + 1) * Marshal.SizeOf(typeof(char))),
                out bytesWritten
            );

            if (!success)
            {
                LogService?.Record(Logs.LOG_WRITE_MEMORY_FAILED);
            }

            return success;
        }

        private bool CreateRemoteThread(IntPtr procHandle, IntPtr loadLibraryAddr, IntPtr allocMemAddress)
        {
            IntPtr threadHandle = Utils.Kernel32.CreateRemoteThread(
                procHandle,
                IntPtr.Zero,
                0,
                loadLibraryAddr,
                allocMemAddress,
                0,
                IntPtr.Zero
            );

            if (threadHandle == IntPtr.Zero)
            {
                LogService?.Record(Logs.LOG_CREATE_THREAD_FAILED);
                return false;
            }

            LogService?.Record(Logs.LOG_THREAD_STARTED);
            Utils.Kernel32.WaitForSingleObject(threadHandle, 5000);
            LogService?.Record(Logs.LOG_THREAD_COMPLETED);
            Utils.Kernel32.CloseHandle(threadHandle);
            return true;
        }

        private void CleanupInjection(IntPtr procHandle, IntPtr allocMemAddress, bool success)
        {
            if (allocMemAddress != IntPtr.Zero && !success)
            {
                LogService?.Record(Logs.LOG_CLEANUP_MEMORY);
                if (Utils.Kernel32.VirtualFreeEx(procHandle, allocMemAddress, 0, Utils.Constants.MEM_RELEASE))
                {
                    LogService?.Record(Logs.LOG_CLEANUP_MEMORY_SUCCESS);
                }
                else
                {
                    LogService?.Record(Logs.LOG_CLEANUP_MEMORY_FAILED);
                }
            }

            if (procHandle != IntPtr.Zero)
            {
                Utils.Kernel32.CloseHandle(procHandle);
            }
        }

        private bool UnloadDll(IntPtr procHandle, IntPtr dllBaseAddr)
        {
            IntPtr freeLibraryAddr = Utils.Kernel32.GetProcAddress(
                Utils.Kernel32.GetModuleHandle("kernel32.dll"),
                "FreeLibrary"
            );

            if (freeLibraryAddr == IntPtr.Zero)
            {
                LogService?.Record(Logs.LOG_GET_FREELIBRARY_FAILED);
                return false;
            }

            IntPtr threadHandle = Utils.Kernel32.CreateRemoteThread(
                procHandle,
                IntPtr.Zero,
                0,
                freeLibraryAddr,
                dllBaseAddr,
                0,
                IntPtr.Zero
            );

            if (threadHandle == IntPtr.Zero)
            {
                LogService?.Record(Logs.LOG_CREATE_EJECTION_THREAD_FAILED);
                return false;
            }

            LogService?.Record(Logs.LOG_THREAD_STARTED);
            Utils.Kernel32.WaitForSingleObject(threadHandle, 5000);
            LogService?.Record(Logs.LOG_THREAD_COMPLETED);
            Utils.Kernel32.CloseHandle(threadHandle);
            return true;
        }

        private IntPtr GetDllBaseAddress(Process process, string dllName)
        {
            foreach (ProcessModule module in process.Modules)
            {
                if (string.Equals(module.ModuleName, dllName, StringComparison.OrdinalIgnoreCase))
                {
                    return module.BaseAddress;
                }
            }
            return IntPtr.Zero;
        }
    }
}
