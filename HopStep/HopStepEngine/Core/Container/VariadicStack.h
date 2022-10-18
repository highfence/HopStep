#pragma once
#include "Core/HopStepOverrides.h"
#include "Core/PrimitiveTypeDefines.h"
#include "Core/Misc/GenericMemory.h"
#include "Core/Misc/DebugUtils.h"


namespace HopStep::Container
{
	using HGenericMemory = ::HopStep::Core::Misc::HGenericMemory;

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
}