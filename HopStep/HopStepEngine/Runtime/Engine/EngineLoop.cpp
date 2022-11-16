#include "EngineLoop.h"
#include "Engine.h"

namespace HopStep
{
    int32 HEngineLoop::Init(const HChar* InCommandLine)
    {
        if (GEngine == nullptr)
        {
            GEngine = new HEngine(this);
        }

        return 0;
    }

    void HEngineLoop::Tick()
    {

    }

    void HEngineLoop::Exit()
    {

    }
}