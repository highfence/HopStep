#pragma once
#include "..\..\Core\CoreExport.h"

namespace HopStep
{
	class IEngineLoop
	{
	public:

		virtual int32 Init(const HChar*) = 0;

		virtual void Tick() = 0;

		virtual void Exit() = 0;
	};

	class HEngineLoop : public IEngineLoop
	{
	public:

		virtual int32 Init(const HChar*) override { return 0; };

		virtual void Tick() override {};

		virtual void Exit() override {};
	};

	extern HEngineLoop GEngineLoop;
}