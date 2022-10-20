#include "Function.h"

namespace HopStep::CoreObject::Reflection
{
	void HNativeFunction::InvokeImpl(void* Instance, HFunctionCallFrame& InvokeFrame, HFUNC_RESULT_DECL)
	{
		HCheck(Instance != nullptr && Func != nullptr);

		Func(Instance, InvokeFrame, HFUNC_RESULT_PARAM);
	}
}
