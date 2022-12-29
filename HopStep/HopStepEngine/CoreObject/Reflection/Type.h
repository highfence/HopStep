#pragma once
#include "..\..\Core\CoreExport.h"

namespace HopStep
{
	/**
	* Object that has name on it.
	* + Metadata managing (todo)
	*/
	class HType
	{
	public:

		HType(const HString& InName);

		virtual ~HType();

		const HString& GetName() const;

	protected:

		HString Name;
	};
}
