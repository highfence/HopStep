#pragma once
#include "Struct.h"

namespace HopStep::CoreObject::Reflection
{
	/**
	 * 
	 */
	class HFunction : public HStruct
	{
	public:
		HFunction(const HString& FunctionName, const HStruct* FunctionOwner = nullptr)
			: HStruct(FunctionName), Owner(FunctionOwner)
		{

		}

		virtual ~HFunction() {};

	private :

		const HStruct* const Owner;

	};

	class HNativeFunction : public HFunction
	{
	public:

	};
}