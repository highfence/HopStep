#pragma once
#include "IDelegateInstance.h"

namespace HopStep::Core::Delegates
{
	/**
	 * Extend IDelegateInstance interface to template
	 */
	template <typename TFunctionType, typename TDelegatePolicy> requires DelegatePolicy<TDelegatePolicy>
	class TBaseDelegateInstance : TDelegatePolicy::HDelegateInstancePolicy
	{
	public:
		
	};

	template <typename TFunctionType, typename TPolicyType, typename TFunctorType, typename... TFunctorVargs>
	class TBaseFunctorDelegateInstance;

	template <typename TReturnType, typename... TParamTypes, typename TPolicyType, typename TFunctorType, typename... TFunctorVargs>
	class TBaseFunctorDelegateInstance<TReturnType(TParamTypes...), TPolicyType, TFunctorType, TFunctorVargs...>
	{
	public:

	};
}