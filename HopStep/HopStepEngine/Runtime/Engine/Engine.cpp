#include "Engine.h"
#include "EngineLoop.h"
#include "..\..\Core\Misc\OutputDevice.h"
#include "..\..\Core\Misc\DebugUtils.h"

namespace HopStep
{
	HEngine* GEngine = nullptr;

	HEngine::HEngine()
	{
	}

	bool HEngine::Execute(const HChar* InCommand, IOutputDevice* InDevice)
	{
		return false;
	}

	void HEngine::Init(IEngineLoop* InLoop)
	{
		EngineLoop = InLoop;
		HCheck(EngineLoop);
	}
}