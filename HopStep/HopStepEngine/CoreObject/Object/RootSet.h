#pragma once
#include "Object.h"
#include "..\..\Intermediate\RootSet.generated.h"

namespace HopStep
{
	HCLASS();
	class HRootSet : public HObject
	{
		DECLARE_CLASS_BODY(HRootSet);

	public:

		virtual bool IsGCRoot() const final { return true; }
	};
}