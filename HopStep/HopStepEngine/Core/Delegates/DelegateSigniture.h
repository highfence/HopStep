#pragma once
#include "DelegateConcepts.h"
#include "IDelegateInstance.h"
#include "DelegateInstances.h"
#include "DelegateBase.h"

namespace HopStep::Core::Delegates
{
	template <typename TDelegateSigniture, typename TDelegatePolicy = HDefaultDelegatePolicy>
	class TDelegate;

	template <typename TReturnType, typename... TParamTypes, typename TDelegatePolicy> 
	class TDelegate<TReturnType(TParamTypes...), TDelegatePolicy> : public TDelegateBase<TDelegatePolicy>
	{
		using Super = TDelegateBase<TDelegatePolicy>;
		using FunctionSignitureType = TReturnType(TParamTypes...);

	public:

		/**
		 * 
		 */
		template <typename TFunctorType, typename... TVarTypes>
		void BindLambda(FunctorType&& Functor, VarTypes... Vars)
		{
			auto LambdaDelegateInstance = CreateLambda();

		}

		/**
		 * 
		 */
		template <typename TFunctorType, typename... TVarTypes>
		[[nodiscard]] static TDelegate<TReturnType(TParamTypes...), TDelegatePolicy> CreateLambda(TFunctorType&& Functor, TVarTypes... Vars)
		{
			TDelegate<TReturnType(TParamTypes...), TDelegatePolicy> Result;
			
			return Result;
		}
	};
}