#pragma once
#include "Core/HopStepOverrides.h"
#include "Core/GenericPlatform/GenericApplicationMessageHandler.h"

namespace HopStep
{
	class HWindowsApplicationMessageHandler : public HGenericApplicationMessageHandler
	{
	public:

		virtual void RegistKeyHandler(TSharedPtr<IInputHandleable> InHandler);

		virtual void HandleKeyUp(uint64* WKey, uint64* LKey) override;

		virtual void HandleKeyDown(uint64* Key, uint64* LKey) override;

	private:

		TArray<TSharedPtr<IInputHandleable>> Handlers;
	};
}
