#pragma once
#include "..\..\Core\CoreStandardIncludes.h"

namespace HopStep
{
	class IGCObject;

	template <class TType>
	concept GarbageCollectable = std::derived_from<TType, HopStep::IGCObject>;
}