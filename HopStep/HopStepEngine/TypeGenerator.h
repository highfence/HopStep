#pragma once

namespace HopStep::Reflection::Internal
{
	template <class TType>
	class HTypeGenerator
	{
	public:
		
		HTypeGenerator(std::wstring_view ClassName) 
			requires requires { TType::StaticClass(); }
			: Name(ClassName)
		{
		}

	protected:

		std::wstring Name;

		uint8 bNative : 1 = false;
	};
}
