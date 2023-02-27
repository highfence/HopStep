#pragma once
#include "Core/HopStepOverrides.h"
#include "Core/GenericPlatform/GenericApplicationMessageHandler.h"

namespace HopStep
{
	class HWindowsApplicationMessageHandler : public HGenericApplicationMessageHandler
	{
	public:

		virtual void RegistKeyHandler(IKeyHandleable* InHandler);

		virtual void HandleKeyUp(uint64* Key);

		virtual void HandleKeyDown(uint64* Key);

	private:

		TArray<IKeyHandleable*> Handlers;
	};
}
