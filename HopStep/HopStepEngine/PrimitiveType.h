#pragma once

namespace HopStep::CoreObject::Reflection
{
	class HPrimitiveType
	{
	public:

		enum class HType : int8_t
		{
			Numeric,
			Boolean,
			String
		};

		explicit HPrimitiveType(HType InType)
			: Type(InType)
		{

		}

		HType Type;
	};
}
