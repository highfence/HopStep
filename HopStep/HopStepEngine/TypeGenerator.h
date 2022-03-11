#pragma once
#include "Type.h"

namespace HopStep::Reflection::Internal
{
	template <class TType>
	class HTypeGenerator
	{
	public:
		
		HTypeGenerator(std::wstring_view ClassName)
			: Name(ClassName)
		{

		}

	protected:

		std::wstring Name;
	};
}
