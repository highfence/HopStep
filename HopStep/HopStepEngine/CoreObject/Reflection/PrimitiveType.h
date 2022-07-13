#pragma once
#include "..\..\Core\HopStepCore.h"

namespace HopStep::CoreObject::Reflection
{
	class HPrimitiveType
	{
	public:

		enum class HStruct : int8_t
		{
			Numeric,
			Boolean,
			String
		};

		explicit HPrimitiveType(HStruct InType)
			: Type(InType)
		{

		}

		HStruct Type;
	};
}
