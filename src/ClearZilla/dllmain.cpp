// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "logging.h"
#include "hooksdecl.h"

// must be all lowercase
LPCWSTR ExeAllowList[] = { L"taskmgr.exe", L"vpnsmgr_x64.exe", L"notepad.exe", L"mspaint.exe" };
constexpr BOOL UseAllowList = FALSE;

LPWSTR ProcessFileName(LPWSTR v)
{
    DWORD idx = 0;
    LPWSTR ret = NULL;
    for (; *v; ++v) {
        if (*v == L'\\')
            ret = v + 1;
        // lowercase
        if (ret) {
            if (*v >= L'A' && *v <= L'Z')
                *v += 32;
        }
    }
    return ret;
}

BOOL CheckExe()
{
    constexpr int allowListCount = sizeof(ExeAllowList) / sizeof(LPCWSTR);

    if (!UseAllowList)
        return TRUE;

    WCHAR moduleName[MAX_PATH];
    if (!GetModuleFileName(NULL, moduleName, MAX_PATH)) {
        dlogp("Error retreiving program name");
    }
    LPWSTR exeName = ProcessFileName(moduleName);
    
    BOOL allowed = FALSE;
    for (int i = 0; i < allowListCount; ++i) {
        if (wcscmp(exeName, ExeAllowList[i]) == 0) {
            allowed = TRUE;
            break;
        }
    }

    dlogp("Program name: %S (%s)", exeName, allowed ? "allow" : "reject");

    return allowed;
}

BOOL SetupHooks()
{
    if (CheckExe()) {
        MH_STATUS stat = MH_Initialize();
        stat = MH_CreateHook(&CreateFontA, &My_CreateFontA, reinterpret_cast<LPVOID*>(&Orig_CreateFontA));
        stat = MH_CreateHook(&CreateFontW, &My_CreateFontW, reinterpret_cast<LPVOID*>(&Orig_CreateFontW));
        stat = MH_CreateHook(&CreateFontIndirectA, &My_CreateFontIndirectA, reinterpret_cast<LPVOID*>(&Orig_CreateFontIndirectA));
        stat = MH_CreateHook(&CreateFontIndirectW, &My_CreateFontIndirectW, reinterpret_cast<LPVOID*>(&Orig_CreateFontIndirectW));
        stat = MH_CreateHook(&CreateFontIndirectExA, &My_CreateFontIndirectExA, reinterpret_cast<LPVOID*>(&Orig_CreateFontIndirectExA));
        stat = MH_CreateHook(&CreateFontIndirectExW, &My_CreateFontIndirectExW, reinterpret_cast<LPVOID*>(&Orig_CreateFontIndirectExW));
        // implement this later when we found a use case for this
        // stat = MH_CreateHook(&GdipSetTextRenderingHint, &My_GdipSetTextRenderingHint, reinterpret_cast<LPVOID*>(&Orig_GdipSetTextRenderingHint));
        stat = MH_EnableHook(MH_ALL_HOOKS);
        return TRUE;
    }
    return FALSE;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    // case DLL_THREAD_ATTACH:
    // case DLL_THREAD_DETACH:
    // case DLL_PROCESS_DETACH:
        return SetupHooks();
    default:
        break;
    }
    // the return value is ignored for anything other than DLL_PROCESS_ATTACH
    return FALSE;
}

