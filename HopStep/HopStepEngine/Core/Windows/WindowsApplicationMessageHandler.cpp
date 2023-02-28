#include "Core/Misc/DebugUtils.h"
#include "WindowsApplicationMessageHandler.h"

namespace HopStep
{
    void HWindowsApplicationMessageHandler::RegistKeyHandler(TSharedPtr<IInputHandleable> InHandler)
    {
        Handlers.push_back(InHandler);
    }

    void HWindowsApplicationMessageHandler::HandleKeyUp(uint64* Key)
    {
        for (TSharedPtr<IInputHandleable> Handler : Handlers)
        {
            Handler->OnKeyUp(Key);
        }
    }

    void HWindowsApplicationMessageHandler::HandleKeyDown(uint64* Key)
    {
        for (TSharedPtr<IInputHandleable> Handler : Handlers)
        {
            Handler->OnKeyDown(Key);
        }
    }
}