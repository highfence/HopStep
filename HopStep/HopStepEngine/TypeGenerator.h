#pragma once
#include "ReflectionConcepts.h"
#include "HopStepOverrides.h"

namespace HopStep::CoreObject::Reflection
{
	template <class TType>
	class HTypeGenerator
	{
	public:

		HTypeGenerator(HStringView ClassName)
			: Name(ClassName)
		{
		}

		HString Name;

		uint8 bNative : 1 = false;
	};
}
