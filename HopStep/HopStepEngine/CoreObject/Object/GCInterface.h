#pragma once
#include "..\..\Core\PrimitiveTypeDefines.h"
#include "..\..\Core\HopStepOverrides.h"

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
		static constexpr uint32 InvalidGCPoolIndex = (uint32)-1;

		virtual uint32 GetGCPoolIndex() const = 0;

		virtual void SetGCPoolIndex(uint32 Index) = 0;

		/**
		 * Properties
		 */
		virtual TArray<IGCObject*> GetGCProperties() = 0;

		/**
		 * References
		 */
		virtual bool IsGCRoot() const = 0;

		virtual bool GetGCMark() const = 0;

		virtual void SetGCMark(bool bMark) = 0;
	};
}
