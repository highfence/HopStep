#include "Engine.h"
#include "EngineLoop.h"
#include "..\..\Core\CoreExport.h"
#include "..\..\Core\Misc\OutputDevice.h"
#include "..\..\Core\Misc\DebugUtils.h"
#include "..\..\Core\Misc\App.h"
#include "..\..\Core\Windows\WindowsPlatformMisc.h"
#include "..\..\Core\GenericPlatform\GenericApplication.h"
#include "..\Render\RenderSystem.h"


namespace HopStep
{
	HEngine* GEngine = nullptr;

	HEngine::HEngine()
		: EngineLoop(nullptr)
		, App(nullptr)
		, RenderSystem(nullptr)
	{
	}

	HEngine::~HEngine()
	{
		if (App)
		{
			delete App;
			App = nullptr;
		}

		if (RenderSystem)
		{
			delete RenderSystem;
			RenderSystem = nullptr;
		}
	}

	bool HEngine::Execute(const HChar* InCommand, IOutputDevice* InDevice)
	{
		return false;
	}

	void HEngine::Init(IEngineLoop* InLoop)
	{
		EngineLoop = InLoop;
		HCheck(EngineLoop);

		App = HPlatformMisc::CreateApplication();
		HCheck(App);

		RenderSystem = IRenderSystem::Create();
		HCheck(RenderSystem);
		HCheck(RenderSystem->Initialize());
	}

	void HEngine::Tick(float Delta)
	{
		App->PumpMessages(Delta);
		RenderSystem->Render();
	}

	void HEngine::UpdateTime()
	{
		static double LastRealTime = HPlatfromTime::Seconds();

		double CurrentRealTime = HPlatfromTime::Seconds();

		HApp::SetCurrentTime(CurrentRealTime);
		HApp::SetDeltaTime(CurrentRealTime - LastRealTime);

		LastRealTime = CurrentRealTime;
	}
}