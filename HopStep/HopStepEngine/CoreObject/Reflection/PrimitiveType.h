#pragma once

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
