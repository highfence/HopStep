#pragma once
#include "Type.h"
#include "FieldClass.h"

namespace HopStep
{
	/**
	 *
	 */
	class HField : public HType
	{
	public:

		HField(const HString& InName, HFieldClass* FieldClass)
			: HType(InName)
			, TypeFlag(static_cast<uint64>(HTypeFlag::None))
			, FieldClassPrivate(FieldClass)
		{
		};

		~HField();

		bool IsPrimitiveType() const { return TypeFlag & static_cast<uint64>(HTypeFlag::Primitive); }

		bool IsClassType() const { return TypeFlag & static_cast<uint64>(HTypeFlag::Class); }

		bool IsContainerType() const { return TypeFlag & static_cast<uint64>(HTypeFlag::Container); }

		bool IsGarbageCollectable() const { return TypeFlag & static_cast<uint64>(HTypeFlag::GarbageCollectable); }

	protected:

		enum class HTypeFlag : uint64
		{
			None = 0x00,
			Primitive = 0x01 << 0,
			Class = 0x01 << 1,
			Container = 0x01 << 2,
			GarbageCollectable = 0x01 << 3
		};


		uint64 TypeFlag;

		HFieldClass* FieldClassPrivate;

		friend struct HStructBuilder;
	};
}

