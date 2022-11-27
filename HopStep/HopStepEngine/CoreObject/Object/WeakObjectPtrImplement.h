#pragma once
#include "..\..\Core\CoreExport.h"
#include "GarbageCollector.h"

namespace HopStep::Internal
{
	class HWeakObjectPtrImplement
	{
	public:

		static bool IsValid(uint32 ObjectIndex, uint32 ObjectSerialNumber);

		static class IGCObject* Get(uint32 ObjectIndex, uint32 ObjectSerialNumber);

	};
}