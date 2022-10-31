#pragma once
#include "..\HopStepOverrides.h"
#include "DelegateHandle.h"

namespace HopStep::Core::Delegates
{
	class IDelegateInstance
	{
	public:

		/**
		 * 
		 */
		virtual ~IDelegateInstance() = default;

		/**
		 * 
		 */
		virtual HopStep::HString GetFunctionName() const = 0;

		/**
		 * 
		 */
		virtual class HObject* GetBoundedObject() const = 0;


	};
}
