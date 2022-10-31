#pragma once
#include "IDelegateInstance.h"
#include "DelegateHandle.h"
#include "..\HopStepOverrides.h"

namespace HopStep::Core::Delegates
{
	/**
	 * Extend IDelegateInstance interface to template
	 */
	template <typename TFunctionType, typename TDelegatePolicy> 
	class IBaseDelegateInstance;
	
	template <typename TReturnType, typename... TArgTypes, typename TDelegatePolicy> requires DelegatePolicy<TDelegatePolicy>
	class IBaseDelegateInstance<TReturnType(TArgTypes...), TDelegatePolicy> : TDelegatePolicy::HDelegateInstancePolicy
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
	 * Implement delegate instances common logics
	 */
	template <typename TFunctionType, typename TDelegatePolicy, typename... TVarTypes> 
	class TCommonDelegateInstance;

	template <typename TReturnType, typename... TParamTypes, typename TDelegatePolicy, typename... TVarTypes> 
	class TCommonDelegateInstance<TReturnType(TParamTypes...), TDelegatePolicy, TVarTypes...> : IBaseDelegateInstance<TReturnType(TParamTypes...), TDelegatePolicy>
	{
	public:

		explicit TCommonTCommonDelegateInstance(TVarTypes... Vars)
			: Payload(Vars...)
		{

		}

	protected:

		TTuple<TVarTypes...> Payload;
	};


	/**
	 * Implement delegate instances common logics
	 */
	template <typename TFunctionType, typename TPolicyType, typename TFunctorType, typename... TFunctorVargs>
	class TBaseFunctorDelegateInstance;

	template <typename TReturnType, typename... TParamTypes, typename TPolicyType, typename TFunctorType, typename... TFunctorVargs>
	class TBaseFunctorDelegateInstance<TReturnType(TParamTypes...), TPolicyType, TFunctorType, TFunctorVargs...>
	{
	public:

	};
}