#pragma once
#include "..\Object\NameTypes.h"

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
	class HField 	
	{
	public:
		typedef HField Super;
		typedef HField ThisClass;

		HField(const HString& InName, class HFieldClass* FieldClass);;

		~HField();

		bool IsPrimitiveType() const { return TypeFlag & static_cast<uint64>(HTypeFlag::Primitive); }

		bool IsClassType() const { return TypeFlag & static_cast<uint64>(HTypeFlag::Class); }

		bool IsContainerType() const { return TypeFlag & static_cast<uint64>(HTypeFlag::Container); }

		bool IsGarbageCollectable() const { return TypeFlag & static_cast<uint64>(HTypeFlag::GarbageCollectable); }

		static class HFieldClass* StaticClass();

		inline static constexpr uint64 StaticClassCastFlagsPrivate();

		inline static constexpr uint64 StaticClassCastFlags();

		inline const HName& GetName() const;

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

		class HFieldClass* FieldClassPrivate;
		HName FieldName;

		friend struct HStructBuilder;
	};
}

