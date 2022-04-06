#pragma once

namespace HopStep::Reflection
{
	template <class TType>
	concept StaticClassGetable = requires(TType Type) 
	{
		requires TType::StaticClass();
	};
}
