#pragma once
#include "..\HopStepOverrides.h"
#include "..\PrimitiveTypeDefines.h"
#include "..\Misc\GenericMemory.h"
#include "..\Misc\DebugUtils.h"

namespace HopStep
{
	using HGenericMemory = ::HopStep::HGenericMemory;

	template <int32 StackSize = 1024>
	struct HVariadicStack
	{
		HVariadicStack()
			: CurrentOffset(0), Count(0)
		{
			HGenericMemory::MemSet(&Storage[0], 0, sizeof(uint8) * StackSize);
		}

		virtual ~HVariadicStack() {};

		void Push(uint8* InData, int16 DataSize);
		void Pop(uint8* OutData, int16 DataSize);

		void PushReference(uint8*& InData);
		void PopReference(uint8*& OutData);

		template <typename TType>
		void PushByType(const TType& InValue);

		template <typename TType> 
		TType PopByType();

		uint16 GetTopOffset() const { return CurrentOffset; }
		const uint8* GetData() const { return &Storage[0]; }

	protected:

		uint8 Storage[StackSize];
		uint16 CurrentOffset;
		uint16 Count;

	};

	template<int32 StackSize>
	inline void HVariadicStack<StackSize>::Push(uint8* InData, int16 DataSize)
	{
		HCheck(CurrentOffset + DataSize <= StackSize);

		HGenericMemory::MemCpy(&Storage[CurrentOffset], InData, DataSize);
		CurrentOffset += DataSize;
		++Count;
	}

	template<int32 StackSize>
	inline void HVariadicStack<StackSize>::Pop(uint8* OutData, int16 DataSize)
	{
		HCheck(CurrentOffset - DataSize >= 0);

		CurrentOffset -= DataSize;
		--Count;
		HGenericMemory::MemCpy(OutData, &Storage[CurrentOffset], DataSize);
	}

	template<int32 StackSize>
	inline void HVariadicStack<StackSize>::PushReference(uint8*& InData)
	{
		int16 DataSize = sizeof(uint8*);
		HCheck(CurrentOffset + DataSize <= StackSize);

		std::uintptr_t CastedData = (uintptr_t)InData;
		Push((uint8*)CastedData, DataSize);
	}

	template<int32 StackSize>
	inline void HVariadicStack<StackSize>::PopReference(uint8*& OutData)
	{
		uintptr_t CastedData;
		Pop((uint8*)&CastedData, sizeof(uintptr_t));
		OutData = (uint8*)CastedData;
	}

	template<int32 StackSize>
	template<typename TType>
	inline void HVariadicStack<StackSize>::PushByType(const TType& InValue)
	{
		Push((uint8*)&InValue, sizeof(TType));
	}

	template<int32 StackSize>
	template<typename TType> 
	inline TType HVariadicStack<StackSize>::PopByType()
	{
		TType Result{};
		Pop((uint8*)&Result, sizeof(TType));
		return Result;
	}
}