#pragma once
#include "..\..\Core\Misc\CommandExecutable.h"

namespace HopStep
{
	/*
	 * 
	 */
	class HEngine : public ICommandExecutable
	{
	public:

		HEngine();

		virtual ~HEngine() {};

		virtual bool Execute(const HChar* InCommand, class IOutputDevice* InDevice) override;

		virtual void Init(class IEngineLoop* InLoop);

	protected:

		class IEngineLoop* EngineLoop;
	};

	/*
	 * Global Engine Pointer. Can be null.
	 */
	extern HEngine* GEngine;
}