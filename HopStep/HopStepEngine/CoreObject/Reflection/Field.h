#pragma once
#include "..\..\Core\HopStepCore.h"

namespace HopStep::CoreObject::Reflection
{
	/**
	* Object that has name on it.
	* + Metadata managing (todo)
	*/
	class HField
	{
	public:

		HField(const HString& InName) : Name(InName) {}

		virtual ~HField() {}

		const HString& GetName() const { return Name; }

	protected:

		HString Name;
	};
}
