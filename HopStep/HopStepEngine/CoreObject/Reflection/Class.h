#pragma once
#include "Struct.h"

namespace HopStep::CoreObject::Reflection
{
	/**
	* Manage Class Default Object (CDO) & Functions
	*/
	class HClass : public HStruct
	{
	public:
		HClass(const HString& InName) : HStruct(InName) {}

		
	};
}