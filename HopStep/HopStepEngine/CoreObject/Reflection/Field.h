#pragma once
#include "..\..\Core\CoreExport.h"

namespace HopStep
{
	/**
	* Object that has name on it.
	* + Metadata managing (todo)
	*/
	class HField
	{
	public:

		HField(const HString& InName);

		virtual ~HField();

		const HString& GetName() const;

	protected:

		HString Name;
	};
}
