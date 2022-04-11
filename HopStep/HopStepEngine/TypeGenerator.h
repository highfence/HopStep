#pragma once
#include "ReflectionConcepts.h"

namespace HopStep::CoreObject::Reflection
{
	template <class TType>
	class HTypeGenerator
	{
	public:

		HTypeGenerator(std::wstring_view ClassName)
			: Name(ClassName)
		{
		}

		std::wstring Name;

		uint8 bNative : 1 = false;
	};
}
