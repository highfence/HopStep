#pragma once
#include "ReflectionConcepts.h"

namespace HopStep::Reflection::Internal
{
	template <StaticClassGetable TDerivedType>
	class HTypeGenerator
	{
	public:
		
		HTypeGenerator(std::wstring_view ClassName) 
			: Name(ClassName)
		{
		}

	protected:

		std::wstring Name;

		uint8 bNative : 1 = false;
	};
}
