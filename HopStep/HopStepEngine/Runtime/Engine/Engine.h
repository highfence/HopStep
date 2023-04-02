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

		/*
		 * Update HApp::DeltaTime
		 */
		virtual void UpdateTime();

		class HWorld* GetWorld() const { return GameWorld.get(); }

	protected:

		class IEngineLoop* EngineLoop;

		class HGenericApplication* App;

		TUniquePtr<class HWorld> GameWorld;
	};

	/*
	 * Global Engine Pointer. Can be null.
	 */
	extern HEngine* GEngine;
}