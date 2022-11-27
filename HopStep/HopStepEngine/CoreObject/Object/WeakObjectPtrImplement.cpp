#include "WeakObjectPtrImplement.h"
#include "GarbageCollector.h"
#include "GCInterface.h"

namespace HopStep::Internal
{
	bool HWeakObjectPtrImplement::IsValid(uint32 ObjectIndex, uint32 ObjectSerialNumber)
	{
		IGCObject* GCObject = HGarbageCollector::GetGCObject(ObjectIndex);

		return GCObject != nullptr && GCObject->GetSerialNumber() == ObjectSerialNumber;
	}

	IGCObject* HWeakObjectPtrImplement::Get(uint32 ObjectIndex, uint32 ObjectSerialNumber)
	{
		if (IsValid(ObjectIndex, ObjectSerialNumber) == false) return nullptr;

		return HGarbageCollector::GetGCObject(ObjectIndex);
	}
}