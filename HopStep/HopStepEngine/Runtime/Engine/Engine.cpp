#include "Engine.h"
#include "EngineLoop.h"
#include "World.h"
#include "..\Render\ID3DRenderer.h"
#include "..\..\Core\CoreExport.h"
#include "..\..\Core\Misc\OutputDevice.h"
#include "..\..\Core\Misc\DebugUtils.h"
#include "..\..\Core\Misc\App.h"
#include "..\..\Core\Windows\WindowsPlatformMisc.h"
#include "..\..\Core\GenericPlatform\GenericApplication.h"


namespace HopStep
{
	HEngine* GEngine = nullptr;

	HEngine::HEngine()
		: EngineLoop(nullptr)
		, App(nullptr)
		, Renderer(nullptr)
		, GameWorld(nullptr)
	{
	}

	HEngine::~HEngine()
	{
		if (App)
		{
			delete App;
			App = nullptr;
		}

		if (Renderer)
		{
			Renderer->OnDestroy();
			delete Renderer;
			Renderer = nullptr;
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

		Renderer = ID3DRenderer::CreateD3DRenderer(App->GetWindow());
		HCheck(Renderer);
		Renderer->OnInit();

		GameWorld = std::make_unique<HWorld>();
		HCheck(GameWorld);
		GameWorld->InitWorld();
	}

	void HEngine::Tick(float Delta)
	{
		App->PumpMessages(Delta);
		Renderer->OnUpdate();
		Renderer->OnRender();
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