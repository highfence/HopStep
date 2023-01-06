#pragma once
#include "Type.h"
#include "FieldClass.h"
#include "ReflectionMacro.h"

namespace HopStep
{
	enum EClassCastFlags : uint64
	{
		CastFlag_None = 0x0000000000000000,
		CastFlag_Field = 0x0000000000000001,
		CastFlag_Property = 0x0000000000000002
	};

	/**
	 *
	 */
	class HField : public HType
	{
	public:
		typedef HField Super;
		typedef HField ThisClass;

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

		static HFieldClass* StaticClass();

		inline static constexpr uint64 StaticClassCastFlagsPrivate()
		{
			return static_cast<uint64>(EClassCastFlags::CastFlag_Field);
		}

		inline static constexpr uint64 StaticClassCastFlags()
		{
			return static_cast<uint64>(EClassCastFlags::CastFlag_Field);
		}

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

