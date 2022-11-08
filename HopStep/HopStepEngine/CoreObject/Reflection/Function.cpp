#include "Function.h"

namespace HopStep
{
	void HNativeFunction::InvokeImpl(void* Instance, HFunctionCallFrame& InvokeFrame, HFUNC_RESULT_DECL_INNER) const
	{
		HCheck(Instance != nullptr && Func != nullptr);

		Func(Instance, InvokeFrame, HFUNC_RESULT_PARAM);
	}
}
