#pragma once
#include "IDelegateInstance.h"
#include "DelegateHandle.h"
#include "DelegateUtils.h"
#include "..\CoreStandardIncludes.h"
#include "..\HopStepOverrides.h"
#include "..\Container\VariadicStack.h"
#include "..\Misc\DebugUtils.h"
#include "..\Templates\RemoveConst.h"

namespace HopStep
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

		virtual HDelegateHandle GetHandle() const override final { return Handle; }

	protected:

		// Todo : Make delegate using payload.
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
		using SignatureReturnType = typename Super::ReturnType;
		using ThisType = TBaseFunctorDelegateInstance<SignatureReturnType(TParamTypes...), TPolicyType, TFunctorType, TFunctorVargs...>;

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
			return Functor(args...);
		};

		/**
		 * 
		 */
		virtual bool ExecuteIfSafe(TParamTypes... args) const override final 
		{
			Functor(args...);
			return true;
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
			return new ThisType(Functor, Vars...);
		}

	private:

		TFunctorType Functor;
	};


	/**
	 * 	Static C++ function delegate instance
	 */
	template <typename TFunctionType, typename TDelegatePolicy, typename... TVarTypes>
	class TBaseStaticDelegateInstance;

	template <typename TReturnType, typename... TParamTypes, typename TDelegatePolicy, typename... TVarTypes>
	class TBaseStaticDelegateInstance<TReturnType(TParamTypes...), TDelegatePolicy, TVarTypes...> : public TCommonDelegateInstance<TReturnType(TParamTypes...), TDelegatePolicy, TVarTypes...>
	{
		using Super = TCommonDelegateInstance<TReturnType(TParamTypes...), TDelegatePolicy, TVarTypes...>;
		using SignatureReturnType = Super::ReturnType;
		using ThisType = TBaseStaticDelegateInstance<TReturnType(TParamTypes...), TDelegatePolicy, TVarTypes...>;

	public:

		using FunctionPtr = SignatureReturnType(*)(TParamTypes..., TVarTypes...);

		TBaseStaticDelegateInstance(FunctionPtr StaticFunctionPtr, TVarTypes... Vars)
			: Super(Vars...), StaticFunctionPtr(StaticFunctionPtr)
		{
			HCheck(StaticFunctionPtr != nullptr);
		}

		/**
		 *
		 */
		virtual TReturnType Execute(TParamTypes... args) const override final
		{
			return StaticFunctionPtr(args...);
		};

		/**
		 *
		 */
		virtual bool ExecuteIfSafe(TParamTypes... args) const override final
		{
			StaticFunctionPtr(args...);
			return true;
		};

		/**
		 * Static delegate instance has no name.
		 */
		virtual HopStep::HString GetFunctionName() const override final
		{
			return HString();
		};

		/**
		 * Static delegate instance has no bounded object.
		 */
		virtual class HObject* GetBoundedObject() const override final
		{
			return nullptr;
		};

		/**
		 * Static delegate instance is always executable.
		 */
		virtual bool IsExecutable() const override { return true; };

		/**
		 * Only create delegate instance with this.
		 */
		static ThisType* Create(FunctionPtr Functor, TVarTypes... Vars)
		{
			return new ThisType(Functor, Vars...);
		}

	private:

		FunctionPtr StaticFunctionPtr;
	};


	/**
	 * 	Class member function delegate instance
	 *  bConst means delegate representing const function or not.
	 */
	template <bool bConst, class TClassType, typename TFunctionType, typename TDelegatePolicy, typename... TVarTypes>
	class TBaseClassMethodDelegateInstance;

	template <bool bConst, class TClassType, typename TReturnType, typename... TParamTypes, typename TDelegatePolicy, typename... TVarTypes>
	class TBaseClassMethodDelegateInstance<bConst, TClassType, TReturnType(TParamTypes...), TDelegatePolicy, TVarTypes...> : public TCommonDelegateInstance<TReturnType(TParamTypes...), TDelegatePolicy, TVarTypes...>
	{
		using Super = TCommonDelegateInstance<TReturnType(TParamTypes...), TDelegatePolicy, TVarTypes...>;
		using SignatureReturnType = typename Super::ReturnType;
		using ThisType = TBaseClassMethodDelegateInstance<bConst, TClassType, TReturnType(TParamTypes...), TDelegatePolicy, TVarTypes...>;

	public:

		using MethodPtrType = typename TClassMethodPointerType<bConst, TClassType, TReturnType(TParamTypes...)>::Type;

		TBaseClassMethodDelegateInstance(TClassType* InClassPtr, MethodPtrType InMethodPtr, TVarTypes... Vars)
			: Super(Vars...)
			, ClassPtr(InClassPtr)
			, MethodPtr(InMethodPtr)
		{
			HCheck(InClassPtr != nullptr && InMethodPtr != nullptr);
		}

		/**
		 *
		 */
		virtual TReturnType Execute(TParamTypes... Args) const override final
		{
			using MutableClassType = typename TRemoveConst<TClassType>::Type;

			MutableClassType* MutableClassObject = const_cast<MutableClassType*>(ClassPtr);

			HCheck(MutableClassObject != nullptr);
			HCheck(MethodPtr != nullptr);

			// Todo : Must be fixed with payloads.
			return (MutableClassObject->*MethodPtr)(Args...);
		};

		/**
		 *
		 */
		virtual bool ExecuteIfSafe(TParamTypes... Args) const override final
		{
			using MutableClassType = typename TRemoveConst<TClassType>::Type;

			MutableClassType* MutableClassObject = const_cast<MutableClassType*>(ClassPtr);

			if (MutableClassObject == nullptr || MethodPtr == nullptr)
			{
				return false;
			}

			// Todo : Must be fixed with payloads.
			(MutableClassObject->*MethodPtr)(Args...);
			return true;
		};

		/**
		 * Static delegate instance has no name.
		 */
		virtual HopStep::HString GetFunctionName() const override final
		{
			return HString();
		};

		/**
		 * Static delegate instance has no bounded object.
		 */
		virtual class HObject* GetBoundedObject() const override final
		{
			return nullptr;
		};

		/**
		 * Static delegate instance is always executable.
		 */
		virtual bool IsExecutable() const override { return true; };

		/**
		 * Only create delegate instance with this.
		 */
		static ThisType* Create(TClassType* ClassPtr, MethodPtrType MethodPtr, TVarTypes... Vars)
		{
			return new ThisType(ClassPtr, MethodPtr, Vars...);
		}

		static ThisType* Create(const TClassType* ClassPtr, MethodPtrType MethodPtr, TVarTypes... Vars)
		{
			return new ThisType(const_cast<TClassType*>(ClassPtr), MethodPtr, Vars...);
		}

	private:

		TClassType* ClassPtr;
		MethodPtrType MethodPtr;
	};

}