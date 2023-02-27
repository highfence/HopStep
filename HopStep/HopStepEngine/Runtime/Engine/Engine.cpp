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
#include "Runtime\Engine\GameCamera.h"
#include "Core\CoreStandardIncludes.h"


namespace HopStep
{
	HEngine* GEngine = nullptr;

	HEngine::HEngine()
		: EngineLoop(nullptr)
		, App(nullptr)
		, Renderer(nullptr)
		, Camera(nullptr)
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

		Camera = std::make_shared<HGameCamera>();
		HCheck(Camera.get());

		App = HPlatformMisc::CreateApplication();
		HCheck(App);
		App->GetMessageHandler().get()->RegistKeyHandler(Camera);

		GameWorld = std::make_unique<HWorld>();
		HCheck(GameWorld);
		GameWorld->InitWorld();

		Renderer = ID3DRenderer::CreateD3DRenderer(App->GetWindow());
		HCheck(Renderer);
		Renderer->OnInit();
	}

	void HEngine::Tick(float Delta)
	{
		App->PumpMessages(Delta);
		// OutputDebugString(Camera->ToString().c_str());
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