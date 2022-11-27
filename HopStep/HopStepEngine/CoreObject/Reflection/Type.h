#pragma once
#include "Field.h"

namespace HopStep
{
	/**
	 * Provides type library to interface
	 */
	class HType : public HField
	{
	public:

		HType(const HString& InName) 
			: HField(InName)
			, TypeFlag(static_cast<uint64>(HTypeFlag::None)) 
		{
		};

		bool IsPrimitiveType() const { return TypeFlag & static_cast<uint64>(HTypeFlag::Primitive); }

		bool IsClassType() const { return TypeFlag & static_cast<uint64>(HTypeFlag::Class); }

		bool IsContainerType() const { return TypeFlag & static_cast<uint64>(HTypeFlag::Container); }

		bool IsGarbageCollectable() const { return TypeFlag & static_cast<uint64>(HTypeFlag::GarbageCollectable); }

	protected:

		void RegisterToLibrary();

		enum class HTypeFlag : uint64
		{
			None = 0x00,
			Primitive = 0x01 << 0,
			Class = 0x01 << 1,
			Container = 0x01 << 2,
			GarbageCollectable  = 0x01 << 3
		};


		uint64 TypeFlag;

		friend struct HStructBuilder;
	};
}
