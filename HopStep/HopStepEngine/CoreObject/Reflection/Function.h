#pragma once
#include "Struct.h"
#include "..\..\Core\Container\VariadicStack.h"
#include "ScriptMacros.h"

namespace HopStep
{
	using HVariadicStack256 = HopStep::HVariadicStack<256>;
	/*
	 */
	struct HFunctionCallFrame : public HVariadicStack256
	{
		HFunctionCallFrame() 
			: HVariadicStack()
		{}
	};

	/*
	 */
	class HFunction : public HStruct
	{
	public:
		HFunction(const HString& FunctionName, const HStruct* FunctionOwner = nullptr)
			: HStruct(FunctionName), Owner(FunctionOwner)
		{

		}

		virtual ~HFunction() {};

		/**
		 * Standard signature of Invoke method
		 */
		template <typename TReturnType, typename... TParamArgs>
		TReturnType Invoke(void* InClassPtr, TParamArgs&&... Args) const;

		/**
		 * No arguments signature of Invoke method
		 */
		template <typename TReturnType>
		TReturnType Invoke(void* InClassPtr) const;

	protected:

		virtual void InvokeImpl(void* Instance, HFunctionCallFrame& InvokeFrame, HFUNC_RESULT_DECL_INNER) const = 0;

		template <typename... TParamArgs>
		void SetParameters(HFunctionCallFrame& RefFrame, TParamArgs&&... Parameters) const;

		template <typename TParamType>
		int16 PushParamter(HFunctionCallFrame& RefFrame, TParamType&& Parameter) const;

		const HStruct* const Owner;

	};

	typedef void (*HNativeFuncPtr)(void* Instance, HFunctionCallFrame& Frame, HFUNC_RESULT_DECL_INNER);

	/*
	 */
	class HNativeFunction : public HFunction
	{
	public:

		HNativeFunction(const HString& FunctionName, const HStruct* FunctionOwner = nullptr, HNativeFuncPtr FuncPtr = nullptr)
			: HFunction(FunctionName, FunctionOwner), Func(FuncPtr)
		{

		}

	protected:

		virtual void InvokeImpl(void* Instance, HFunctionCallFrame& InvokeFrame, HFUNC_RESULT_DECL_INNER) const override;

		HNativeFuncPtr Func;
	};

	template<typename TReturnType, typename ...TParamArgs>
	inline TReturnType HFunction::Invoke(void* InClassPtr, TParamArgs && ...Args) const
	{
		HFunctionCallFrame Frame;

		SetParameters(Frame, Args...);

		HFUNC_RESULT_DECL = nullptr;
		InvokeImpl(InClassPtr, Frame, &HFUNC_RESULT_PARAM);

#if HOPSTEP_USING_STD_ANY
		return std::any_cast<TReturnType>(HFUNC_RESULT_PARAM);
#else
		return (TReturnType)HFUNC_RESULT_PARAM;
#endif
	}

	template<typename TReturnType>
	inline TReturnType HFunction::Invoke(void* InClassPtr) const
	{
		HFunctionCallFrame Frame;

		HFUNC_RESULT_DECL = nullptr;
		InvokeImpl(InClassPtr, Frame, &HFUNC_RESULT_PARAM);

#if HOPSTEP_USING_STD_ANY
		return std::any_cast<TReturnType>(HFUNC_RESULT_PARAM);
#else
		return (TReturnType)HFUNC_RESULT_PARAM;
#endif
	}

	template<typename... TParamArgs>
	void HFunction::SetParameters(HFunctionCallFrame& RefFrame, TParamArgs&&... Parameter) const
	{
		auto _ = { PushParamter(RefFrame, Parameter)... };
	}

	template <typename TParamType>
	int16 HFunction::PushParamter(HFunctionCallFrame& RefFrame, TParamType&& Parameter) const
	{
		RefFrame.PushByType<TParamType>(Parameter);
		return 0;
	}

}