#include "pch.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <tchar.h>
#include "../ControlSum/Header.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    // 0 for dynamic load, not 0 - for static
    std::cout << "lpReserved: " << lpReserved << std::endl;

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {
        TCHAR* name = new TCHAR[256];
        GetModuleFileName(hModule, name, 256);
        std::ifstream file(name, std::ios::binary);
        uint64_t real = checkSum(file);
        uint64_t written = readSum(file);
        
        if (real != written) {
            std::cout << "ERROR! Check sums don't match." << std::endl;
            return FALSE;
        }
        std::cout << "Check sum has been checked." << std::endl;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}