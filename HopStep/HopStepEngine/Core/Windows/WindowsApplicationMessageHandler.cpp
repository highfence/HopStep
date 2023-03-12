#include "Core/Misc/DebugUtils.h"
#include "WindowsApplicationMessageHandler.h"

namespace HopStep
{
    void HWindowsApplicationMessageHandler::RegistKeyHandler(TSharedPtr<IInputHandleable> InHandler)
    {
        Handlers.push_back(InHandler);
    }

	void HWindowsApplicationMessageHandler::HandleKeyUp(uint64* WKey, uint64* LKey)  
    {
        for (TSharedPtr<IInputHandleable> Handler : Handlers)
        {
            Handler->OnKeyUp(WKey, LKey);
        }
    }

    void HWindowsApplicationMessageHandler::HandleKeyDown(uint64* WKey, uint64* LKey)
    {
        for (TSharedPtr<IInputHandleable> Handler : Handlers)
        {
            Handler->OnKeyDown(WKey, LKey);
        }
    }
}