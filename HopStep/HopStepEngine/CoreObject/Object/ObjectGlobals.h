#pragma once
#include "..\..\Core\CoreExport.h"

namespace HopStep::Internal
{
	enum class EPropertyGenFlags : uint32
	{
		None = 0x00,
		
		// ���� 6��Ʈ�� Property Type�� �Ҵ� �ȴٰ� �Ѵ�
		// �� �� 2��Ʈ�� �츮�� Property�� ������ ������ �� �� �ִ�.
		Byte = 0x00,
		Int8 = 0x01,
		Int16 = 0x02,
		Int32 = 0x03,
		Int64 = 0x04,
		UInt16 = 0x05,
		UInt32 = 0x06,
		UInt64 = 0x07,
		Float = 0x08,
		Double = 0x09,
		Bool = 0x0A,
		Class = 0x0B,
		Interface = 0x0C,
		Name = 0x0D,
		String = 0x0E,
		Array = 0x0F,
		Map = 0x10,
		Set = 0x11,
		Struct = 0x12,
		Delegate = 0x13,
		Enum = 0x14,

		ObjectPtr = 0x15
	};

	struct HPropertyParamBase
	{
		const HChar* Name;
		int32 Offset;
		int32 ArrayDimension;
		EPropertyGenFlags Flags;
	};

	// Todo: Add ClassPropertyParam struct here when HObject needs specialized constructor
}