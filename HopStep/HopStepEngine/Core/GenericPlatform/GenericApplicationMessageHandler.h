#pragma once
#include "Core/PrimitiveTypeDefines.h"
#include "Core/Misc/DebugUtils.h"
#include "Core/HopStepOverrides.h"

namespace HopStep
{
	class IInputHandleable
	{
	public:

		virtual void OnKeyDown(uint64* WKey, uint64* LKey) = 0;

		virtual void OnKeyUp(uint64* WKey, uint64* LKey) = 0;
	};

	class HGenericApplicationMessageHandler
	{
	public:

		virtual ~HGenericApplicationMessageHandler() {};

		virtual void RegistKeyHandler(TSharedPtr<IInputHandleable> InHandler) { HCheck(false); };

		virtual void HandleKeyUp(uint64* WKey, uint64* LKey) { HCheck(false); };

		virtual void HandleKeyDown(uint64* Key, uint64* LKey) { HCheck(false); };
	};
}