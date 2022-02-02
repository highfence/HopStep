#pragma once

namespace HopStep::Reflection
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

