#include "Core/Misc/DebugUtils.h"
#include "WindowsApplicationMessageHandler.h"

namespace HopStep
{
    void HWindowsApplicationMessageHandler::RegistKeyHandler(IKeyHandleable* InHandler)
    {
        HCheck(InHandler != nullptr);
        Handlers.push_back(InHandler);
    }

    void HWindowsApplicationMessageHandler::HandleKeyUp(uint64* Key)
    {
        for (IKeyHandleable* Handler : Handlers)
        {
            Handler->OnKeyUp(Key);
        }
    }

    void HWindowsApplicationMessageHandler::HandleKeyDown(uint64* Key)
    {
        for (IKeyHandleable* Handler : Handlers)
        {
            Handler->OnKeyDown(Key);
        }
    }
}