#include "Object.h"
#include "ObjectPtr.h"

namespace HopStep
{
	bool operator==(HObjectHandle LHS, HObjectHandle RHS)
	{
		return LHS.PointerOrRef == RHS.PointerOrRef;
	}

	bool operator!=(HObjectHandle LHS, HObjectHandle RHS)
	{
		return !(LHS == RHS);
	}

	HObjectHandle MakeObjectHandle(HObject* InObject)
	{
		return HObjectHandle{ .PointerOrRef = (intptr_t)InObject };
	}

	HObject* ResolveObjectHandle(const HObjectHandle& InHandle)
	{
		return reinterpret_cast<HObject*>(InHandle.PointerOrRef);
	}

}