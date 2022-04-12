#pragma once
#include "HopStepOverrides.h"

namespace HopStep::CoreObject::Reflection
{
	/**
	* Object that has name on it.
	*/
	class HField
	{
	public:

		HField(HString& InName) : Name(InName) {}

		virtual ~HField() {}

		const HString& GetName() const { return Name; }

	protected:

		HString Name;
	};
}
