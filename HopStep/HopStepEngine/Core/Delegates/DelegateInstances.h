#pragma once
#include "IDelegateInstance.h"

namespace HopStep::Core::Delegates
{
	/**
	 * Extend IDelegateInstance interface to template
	 */
	template <typename TFunctionType, typename TDelegatePolicy> 
	class TBaseDelegateInstance;
	
	template <typename TReturnType, typename... TArgTypes, typename TDelegatePolicy> requires DelegatePolicy<TDelegatePolicy>
	class TBaseDelegateInstance<TReturnType(TArgTypes...), TDelegatePolicy> : TDelegatePolicy::HDelegateInstancePolicy
	{
	public:

		/**
		 * Execute delegate instance. 
		 */
		virtual TReturnType Execute(TArgTypes...) const = 0;

		/**
		 * Execute delegate instance. But support only with no return value delegate.
		 */
		virtual bool ExecuteIfSafe(TArgTypes...) const = 0;
	};

	/**
	 * 
	 */

	template <typename TFunctionType, typename TPolicyType, typename TFunctorType, typename... TFunctorVargs>
	class TBaseFunctorDelegateInstance;

	template <typename TReturnType, typename... TParamTypes, typename TPolicyType, typename TFunctorType, typename... TFunctorVargs>
	class TBaseFunctorDelegateInstance<TReturnType(TParamTypes...), TPolicyType, TFunctorType, TFunctorVargs...>
	{
	public:

	};
}