#pragma once
#include "Field.h"

namespace HopStep::CoreObject::Reflection
{
	/**
	 * Provides type library to interface
	 */
	class HType : public HField
	{
	public:

		explicit HType(const HString& InName) : HField(InName) {};

	protected:

		void RegisterToLibrary();
	};
}
