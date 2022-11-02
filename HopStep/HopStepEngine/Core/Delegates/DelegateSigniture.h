#pragma once
#include "DelegateConcepts.h"
#include "IDelegateInstance.h"
#include "DelegateInstances.h"
#include "DelegateBase.h"
#include "DelegateUtils.h"
#include "..\Templates\HopStepTemplates.h"
#include "..\Misc\DebugUtils.h"

namespace HopStep::Core::Delegates
{
	template <typename TDelegateSigniture, typename TDelegatePolicy = HDefaultDelegatePolicy>
	class TDelegate;

	template <typename TReturnType, typename... TParamTypes, typename TDelegatePolicy>
	class TDelegate<TReturnType(TParamTypes...), TDelegatePolicy> : public TDelegateBase<TDelegatePolicy>
	{
		using Super = TDelegateBase<TDelegatePolicy>;
		using FunctionSignitureType = TReturnType(TParamTypes...);
		using DelegateInstanceType = IBaseDelegateInstance<FunctionSignitureType, TDelegatePolicy>;

	public:

		virtual ~TDelegate()
		{
			Unbind();
		}

		/**
		 * Remove InstancePtr only though this method.
		 */
		void Unbind()
		{
			if (InstancePtr)
			{
				delete InstancePtr;
			}

			InstancePtr = nullptr;
		}

		/**
		 *
		 */
		TReturnType Execute(TParamTypes... Params) const
		{
			HCheck(InstancePtr);

			return InstancePtr->Execute(Params...);
		}

		/**
		 *
		 */
		template <typename TempReturnType = TReturnType, std::enable_if_t<std::is_void<TempReturnType>::value>* = nullptr>
		bool ExecuteIfBound(TParamTypes... Params) const
		{
			if (InstancePtr)
			{
				return InstancePtr->ExecuteIfSafe(Params...);
			}

			return false;
		}

		/**
		 * Make TBaseFunctorDelegateInstance for Lambda functions.
		 */
		template <typename TFunctorType, typename... TVarTypes>
		void BindLambda(TFunctorType&& Functor, TVarTypes... Vargs)
		{
			Unbind();

			InstancePtr = static_cast<DelegateInstanceType*>(TBaseFunctorDelegateInstance<FunctionSignitureType, TDelegatePolicy, typename TRemoveReference<TFunctorType>::Type, TVarTypes...>::Create(Forward<TFunctorType>(Functor), Vargs...));
		}

		/**
		 * Make delegate instance for C++ pointer global functions.
		 */
		template <typename... TVarTypes>
		void BindStatic(typename TBaseStaticDelegateInstance<FunctionSignitureType, TDelegatePolicy, TVarTypes...>::FunctionPtr Function, TVarTypes... Vars)
		{
			Unbind();

			InstancePtr = static_cast<DelegateInstanceType*>(TBaseStaticDelegateInstance<FunctionSignitureType, TDelegatePolicy, TVarTypes...>::Create(Function, Vars...));
		}

		/**
		 * Make delegate instance for C++ class method functions.
		 */
		template <typename TClassType, typename... TVarTypes>
		void BindMethod(TClassType* InClassObject, typename TClassMethodPointerType<false, TClassType, FunctionSignitureType>::Type InMethod, TVarTypes... Vars)
		{
			Unbind();

			InstancePtr = static_cast<DelegateInstanceType*>(TBaseClassMethodDelegateInstance<false, TClassType, FunctionSignitureType, TDelegatePolicy, TVarTypes...>::Create(InClassObject, InMethod, Vars...));
		}

		template <typename TClassType, typename... TVarTypes>
		void BindMethod(const TClassType* InClassObject, typename TClassMethodPointerType<true, TClassType, FunctionSignitureType>::Type InMethod, TVarTypes... Vars)
		{
			Unbind();

			InstancePtr = static_cast<DelegateInstanceType*>(TBaseClassMethodDelegateInstance<true, TClassType, FunctionSignitureType, TDelegatePolicy, TVarTypes...>::Create(InClassObject, InMethod, Vars...));
		}


	protected:

		DelegateInstanceType* InstancePtr = nullptr;
	};
}