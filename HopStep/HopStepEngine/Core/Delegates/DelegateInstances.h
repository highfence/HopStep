#pragma once
#include "IDelegateInstance.h"
#include "DelegateHandle.h"
#include "..\HopStepOverrides.h"
#include "..\Container\VariadicStack.h"

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
	 * But still, abstract.
	 */
	template <typename TFunctionType, typename TDelegatePolicy, typename... TVarTypes> 
	class TCommonDelegateInstance;

	template <typename TReturnType, typename... TParamTypes, typename TDelegatePolicy, typename... TVarTypes> 
	class TCommonDelegateInstance<TReturnType(TParamTypes...), TDelegatePolicy, TVarTypes...> : public IBaseDelegateInstance<TReturnType(TParamTypes...), TDelegatePolicy>
	{
	public:

		using ReturnType = TReturnType;

		explicit TCommonDelegateInstance(TVarTypes... Vars)
			: Payload(std::make_tuple(Vars...))
			, Handle(HDelegateHandle::EDelegateHandleGenerateType::NewHandleIDGenerate)
		{

		}

		virtual HDelegateHandle GetHandle() const override { return Handle; }

	protected:

		std::tuple<TVarTypes...> Payload;
		HDelegateHandle Handle;
	};


	/**
	 * Lambda function delegate instance.	
	 */
	template <typename TFunctionType, typename TPolicyType, typename TFunctorType, typename... TFunctorVargs>
	class TBaseFunctorDelegateInstance;

	template <typename TReturnType, typename... TParamTypes, typename TPolicyType, typename TFunctorType, typename... TFunctorVargs>
	class TBaseFunctorDelegateInstance<TReturnType(TParamTypes...), TPolicyType, TFunctorType, TFunctorVargs...> : public TCommonDelegateInstance<TReturnType(TParamTypes...), TPolicyType, TFunctorVargs...>
	{
		using Super = TCommonDelegateInstance<TReturnType(TParamTypes...), TPolicyType, TFunctorVargs...>;
		using SuperReturnType = typename Super::ReturnType;
		using ThisType = TBaseFunctorDelegateInstance<SuperReturnType(TParamTypes...), TPolicyType, TFunctorType, TFunctorVargs...>;

	public:

		TBaseFunctorDelegateInstance(const TFunctorType& Functor, TFunctorVargs... Vars)
			: Super(Vars...)
			, Functor(Functor)
		{

		}

		/**
		 * 
		 */
		virtual TReturnType Execute(TParamTypes... args) const override final 
		{

			return TReturnType(); 
		};

		/**
		 * 
		 */
		virtual bool ExecuteIfSafe(TParamTypes... args) const override final 
		{
			return false; 
		};

		/**
		 * Functor delegate instance has no name.
		 */
		virtual HopStep::HString GetFunctionName() const override final
		{
			return HString(); 
		};

		/**
		 * Functor delegate instance has no bounded object.
		 */
		virtual class HObject* GetBoundedObject() const override final 
		{
			return nullptr; 
		};

		/**
		 * Functor delegate instance is always executable.
		 */
		virtual bool IsExecutable() const override { return true; };

		/**
		 * Only create delegate instance with this.
		 */
		static ThisType* Create(TFunctorType&& Functor, TFunctorVargs... Vars)
		{
			return new ThisType(Functor, Vars...);
		}

		static ThisType* Create(const TFunctorType& Functor, TFunctorVargs... Vars)
		{
			return new ThisType(std::move(Functor), Vars...);
		}

	private:

		TFunctorType Functor;
	};
}