#pragma once
#include "Core/PrimitiveTypeDefines.h"
#include "Core/Misc/DebugUtils.h"
#include "Core/HopStepOverrides.h"

namespace HopStep
{
	class IInputHandleable
	{
	public:

		virtual void OnKeyDown(uint64* Key) = 0;

		virtual void OnKeyUp(uint64* Key) = 0;
	};

	class HGenericApplicationMessageHandler
	{
	public:

		virtual ~HGenericApplicationMessageHandler() {};

		virtual void RegistKeyHandler(TSharedPtr<IInputHandleable> InHandler) { HCheck(false); };

		virtual void HandleKeyUp(uint64* Key) { HCheck(false); };

		virtual void HandleKeyDown(uint64* Key) { HCheck(false); };
	};
}