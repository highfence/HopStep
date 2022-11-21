#pragma once
#include "..\..\Core\PrimitiveTypeDefines.h"

namespace HopStep
{
	/**
	 * Who wants to managed by Garbage collector, must inherit this interface.
	 */
	class IGCObject
	{
	public:

		virtual ~IGCObject() = default;

		/**
		 * Pool Index
		 */
		static constexpr uint32 InvalidPoolIndex = (uint32)-1;
		virtual uint32 GetPoolIndex() const = 0;
		virtual void SetPoolIndex(uint32 Index) = 0;


	};
}
