#include "aimbot.h"
#include <wtypes.h>
#include <wtypes.h>
#include <Windows.h>
#include "../external-cheat-base/memory/memory.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    aimbot::procId = VARS::processId;
    aimbot::modulebase = VARS::GetModuleBaseAddress(aimbot::procId, L"client.dll");

    while (true) {
        if (GetAsyncKeyState(VK_LMENU))
            aimbot::frame();
    }

    return 0;
}