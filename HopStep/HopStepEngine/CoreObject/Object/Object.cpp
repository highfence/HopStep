#include "..\Reflection\Property.h"
#include "Object.h"

namespace HopStep
{
	void HObject::GetGCProperties(TArray<IGCObject*>& OutList) 
	{
		HClass* ThisClass = GetClass();

		const TArray<HProperty*> Properties = ThisClass->GetProperties();

		// Todo: Recursive
		for (HProperty* Property : Properties)
		{
			if (Property == nullptr || Property->IsPrimitiveType()) continue;
			if (Property->IsGarbageCollectable() == false) continue;

			HObjectBase* BasePtr = reinterpret_cast<HObjectBase*>(this);
			IGCObject* GCPtr = nullptr;

			// Todo: How can i do this?

			OutList.push_back(GCPtr);
		}
	}

	bool HObject::IsGCRoot() const
	{
		return bIsGCRoot;
	}

	void HObject::SetGCRoot(bool bIsRoot)
	{
		bIsGCRoot = bIsRoot;
	}

	bool HObject::GetGCMark() const
	{
		return bMarked;
	}

	void HObject::SetGCMark(bool bMark)
	{
		bMarked = bMark;
	}

	void HObject::SetSerialNumber(uint32 InSerialNumber)
	{
		SerialNumber = InSerialNumber;
	}

	uint32 HObject::GetSerialNumber() const
	{
		return SerialNumber;
	}
}
