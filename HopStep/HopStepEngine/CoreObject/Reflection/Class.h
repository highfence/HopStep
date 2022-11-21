#pragma once
#include "Struct.h"
#include "Function.h"
#include "..\..\Core\HopStepOverrides.h"

namespace HopStep
{
	/**
	* Manage Class Default Object (CDO) & Functions
	*/
	class HClass : public HStruct
	{
	public:

		HClass(const HString& InName) : HStruct(InName) {}

		/**
		 *
		 */
		const TArray<HFunction*> GetFunctions() const;

		/**
		 *
		 */
		const HFunction* FindFunction(const HString& FunctionName) const;

	protected:


		friend struct HStructBuilder;

		TArray<HUniquePtr<HFunction>> Functions;
	};
}
