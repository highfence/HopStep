#include "EngineLoop.h"
#include "Engine.h"
#include "..\..\Core\CoreExport.h"
#include "..\..\Core\Windows\WindowsPlatformMisc.h"
#include "Runtime/Engine/World.h"

namespace HopStep
{
    int32 HEngineLoop::Init(const HChar* InCommandLine)
    {
        if (GEngine == nullptr)
        {
            GEngine = new HEngine();
        }

        GEngine->Init(this);

        return 0;
    }

    void HEngineLoop::Tick()
    {
        // Rendering tickable object update (If rendering thread doesn't exist)

        // Engine Tick
        GEngine->UpdateTime();

        const float DeltaTime = static_cast<float>(HApp::GetDeltaTime());

        HWorld* GameWorld = GEngine->GetWorld();

        GameWorld->Tick(DeltaTime);
    }

    void HEngineLoop::Exit()
    {
        // Todo: don't do this. make engine class garbage collectable.
        if (GEngine)
        {
            delete GEngine;
            GEngine = nullptr;
        }
    }
}