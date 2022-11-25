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


	protected:

		void RegisterToLibrary();

		enum class HTypeFlag : uint64
		{
			None = 0x00,
			Primitive = 0x01 << 0,
			Class = 0x01 << 1,
			Container = 0x01 << 2
		};

		uint64 TypeFlag;
	};
}
