#pragma once
#include "Struct.h"
#include "..\..\Core\Container\VariadicStack.h"
#include "ScriptMacros.h"

namespace HopStep::CoreObject::Reflection
{
	using HVariadicStack256 = HopStep::Container::HVariadicStack<256>;
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

		template <typename TReturnType, typename... TParamArgs>
		TReturnType Invoke(void* InClassPtr, TParamArgs&&... Args) const;

	protected:

		virtual void InvokeImpl(void* Instance, HFunctionCallFrame& InvokeFrame, HFUNC_RESULT_DECL_INNER) const abstract;

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

		return (TReturnType)HFUNC_RESULT_PARAM;
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