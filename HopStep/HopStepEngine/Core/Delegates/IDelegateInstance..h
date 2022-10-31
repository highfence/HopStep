#pragma once
#include "..\HopStepOverrides.h"

namespace HopStep::Core::Delegates
{
	class IDelegateInstance
	{
	public:

		virtual ~IDelegateInstance() = default;

		virtual HopStep::HString GetFunctionName() const = 0;
	};
}
