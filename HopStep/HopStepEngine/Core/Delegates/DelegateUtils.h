#pragma once

namespace HopStep::Core::Delegates
{
	/**
	 * Helper template for class method type define.
	 */
	template <bool bConst, typename TClass, typename TFunctionSignature>
	struct TClassMethodPointerType;

	template <typename TClass, typename TReturnType, typename... TArgTypes>
	struct TClassMethodPointerType<false, TClass, TReturnType(TArgTypes...)>
	{
		typedef TReturnType(TClass::* Type)(TArgTypes...);
	};
		
	template <typename TClass, typename TReturnType, typename... TArgTypes>
	struct TClassMethodPointerType<true, TClass, TReturnType(TArgTypes...)>
	{
		typedef TReturnType(TClass::* Type)(TArgTypes...) const;
	};
}
