#pragma once

namespace HopStep::Reflection::Internal
{
	template <class TDerivedType>
	class HTypeGenerator
	{
	public:
		
		HTypeGenerator(std::wstring_view ClassName) 
			requires requires { TDerivedType::StaticClass(); }
			: Name(ClassName)
		{
		}

	protected:

		std::wstring Name;

		uint8 bNative : 1 = false;
	};
}
