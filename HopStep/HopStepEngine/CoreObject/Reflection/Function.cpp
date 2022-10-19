#include "Function.h"

namespace HopStep::CoreObject::Reflection
{
	void HNativeFunction::InvokeImpl(void* Instance, HFunctionCallFrame& InvokeFrame, RESULT_DECL)
	{
		HCheck(Instance != nullptr && Func != nullptr);

		Func(Instance, InvokeFrame, RESULT_PARAM);
	}
}
