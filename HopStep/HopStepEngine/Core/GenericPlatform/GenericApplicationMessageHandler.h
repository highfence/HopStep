#pragma once
#include "Core/PrimitiveTypeDefines.h"
#include "Core/Misc/DebugUtils.h"

namespace HopStep
{
	class IKeyHandleable
	{
	public:

		virtual void OnKeyDown(uint64* Key) = 0;
		virtual void OnKeyUp(uint64* Key) = 0;
	};

	class HGenericApplicationMessageHandler
	{
	public:

		virtual ~HGenericApplicationMessageHandler() {};

		virtual void RegistKeyHandler(IKeyHandleable* InHandler) { HCheck(false); };

		virtual void HandleKeyUp(uint64* Key) { HCheck(false); };

		virtual void HandleKeyDown(uint64* Key) { HCheck(false); };
	};
}