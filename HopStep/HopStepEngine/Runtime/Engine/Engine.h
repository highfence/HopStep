#pragma once
#include "..\..\Core\CoreExport.h"

namespace HopStep
{
	/*
	 * 
	 */
	class HEngine : public ICommandExecutable
	{
	public:

		HEngine();

		virtual ~HEngine();

		virtual bool Execute(const HChar* InCommand, class IOutputDevice* InDevice) override;

		virtual void Init(class IEngineLoop* InLoop);

		virtual void Tick(float Delta);

		/*
		 * Update HApp::DeltaTime
		 */
		virtual void UpdateTime();

	protected:

		class IEngineLoop* EngineLoop;

		class HGenericApplication* App;

		class ID3DRenderer* Renderer;

		TSharedPtr<class HGameView> View;

		TUniquePtr<class HWorld> GameWorld;
	};

	/*
	 * Global Engine Pointer. Can be null.
	 */
	extern HEngine* GEngine;
}