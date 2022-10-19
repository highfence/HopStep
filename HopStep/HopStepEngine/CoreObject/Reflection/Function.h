#pragma once
#include "Struct.h"
#include "Core\Container\VariadicStack.h"

namespace HopStep::CoreObject::Reflection
{
	using HVariadicStack = HopStep::Container::HVariadicStack<256>;
	/*
	 */
	struct HDirectionFunctionCallFrame : public HVariadicStack
	{
		HDirectionFunctionCallFrame() 
			: HVariadicStack()
			, OutputOffset(0)
			, OutputSize(0) 
		{}

		void PushOutput(uint8* Output, int16 Size)
		{
			int16 Offset = GetTopOffset();
			Push(Output, Size);
			OutputOffset = Offset;
			OutputSize = Size;
		}

		template <typename TOutType>
		TOutType PopOutput()
		{
			HCheck(OutputSize == sizeof(TOutType));
			TOutType Output;
			Pop((uint8*)&Output, OutputSize);
			return Output;
		}

	protected:

		int16 OutputOffset;
		int16 OutputSize;
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

		virtual void InvokeImpl(HDirectionFunctionCallFrame& InvokeFrame) abstract;

		template <typename... TParamArgs>
		void SetParameters(HDirectionFunctionCallFrame& RefFrame, TParamArgs&&... Parameters);

		template <typename TParamType>
		int16 PushParamter(HDirectionFunctionCallFrame& RefFrame, TParamType&& Parameter);

		const HStruct* const Owner;

	};

	typedef void (*HNativeFuncPtr)(HDirectionFunctionCallFrame& Frame);

	/*
	 */
	class HNativeFunction : public HFunction
	{
	public:

		HNativeFunction(const HString& FunctionName, const HStruct* FunctionOwner = nullptr)
			: HFunction(FunctionName, FunctionOwner)
		{

		}

	protected:

		virtual void InvokeImpl(HDirectionFunctionCallFrame& InvokeFrame) override;

		HNativeFuncPtr Func;
	};

	template<typename TReturnType, typename ...TParamArgs>
	inline TReturnType HFunction::Invoke(void* InClassPtr, TParamArgs && ...Args)
	{
		HDirectionFunctionCallFrame Frame;

		uint8* ClassReference = (uint8*)InClassPtr;
		Frame.PushReference(ClassReference);

		SetParameters(Frame, Args);

		return Frame.PopByType
	}

	template<typename... TParamArgs>
	void HFunction::SetParameters(HDirectionFunctionCallFrame& RefFrame, TParamArgs&&... Parameter)
	{
		auto _ = { PushParamter(RefFrame, Parameter)... };
	}

	template <typename TParamType>
	int16 HFunction::PushParamter(HDirectionFunctionCallFrame& RefFrame, TParamType&& Parameter)
	{
		RefFrame.PushByType<TParamType>(Parameter);
		return 0;
	}

}