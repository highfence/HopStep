#pragma once
#include "Struct.h"
#include "Core\Container\VariadicStack.h"
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
		TReturnType Invoke(void* InClassPtr, TParamArgs&&... Args);

	protected:

		virtual void InvokeImpl(void* Instance, HFunctionCallFrame& InvokeFrame, HFUNC_RESULT_DECL) abstract;

		template <typename... TParamArgs>
		void SetParameters(HFunctionCallFrame& RefFrame, TParamArgs&&... Parameters);

		template <typename TParamType>
		int16 PushParamter(HFunctionCallFrame& RefFrame, TParamType&& Parameter);

		const HStruct* const Owner;

	};

	typedef void (*HNativeFuncPtr)(void* Instance, HFunctionCallFrame& Frame, HFUNC_RESULT_DECL);

	/*
	 */
	class HNativeFunction : public HFunction
	{
	public:

		HNativeFunction(const HString& FunctionName, const HStruct* FunctionOwner = nullptr)
			: HFunction(FunctionName, FunctionOwner), Func(nullptr)
		{

		}

	protected:

		virtual void InvokeImpl(void* Instance, HFunctionCallFrame& InvokeFrame, HFUNC_RESULT_DECL) override;

		HNativeFuncPtr Func;
	};

	template<typename TReturnType, typename ...TParamArgs>
	inline TReturnType HFunction::Invoke(void* InClassPtr, TParamArgs && ...Args)
	{
		HFunctionCallFrame Frame;

		SetParameters(Frame, Args);

		HFUNC_RESULT_DECL;
		InvokeImpl(InClassPtr, Frame, HFUNC_RESULT_PARAM);

		return HFUNC_RESULT_PARAM;
	}

	template<typename... TParamArgs>
	void HFunction::SetParameters(HFunctionCallFrame& RefFrame, TParamArgs&&... Parameter)
	{
		auto _ = { PushParamter(RefFrame, Parameter)... };
	}

	template <typename TParamType>
	int16 HFunction::PushParamter(HFunctionCallFrame& RefFrame, TParamType&& Parameter)
	{
		RefFrame.PushByType<TParamType>(Parameter);
		return 0;
	}

}