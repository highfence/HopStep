#include "Core/Misc/DebugUtils.h"
#include "WindowsApplicationMessageHandler.h"

namespace HopStep
{
    void HWindowsApplicationMessageHandler::RegistKeyHandler(TSharedPtr<IKeyHandleable> InHandler)
    {
        Handlers.push_back(InHandler);
    }

    void HWindowsApplicationMessageHandler::HandleKeyUp(uint64* Key)
    {
        for (TSharedPtr<IKeyHandleable> Handler : Handlers)
        {
            Handler->OnKeyUp(Key);
        }
    }

    void HWindowsApplicationMessageHandler::HandleKeyDown(uint64* Key)
    {
        for (TSharedPtr<IKeyHandleable> Handler : Handlers)
        {
            Handler->OnKeyDown(Key);
        }
    }
}