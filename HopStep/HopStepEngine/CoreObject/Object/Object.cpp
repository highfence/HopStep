#include "..\Reflection\Property.h"
#include "Object.h"

namespace HopStep
{
	void HObject::GetGCProperties(TArray<IGCObject*>& OutList) 
	{
		HClass* ThisClass = GetClass();

		const TArray<HProperty*> Properties = ThisClass->GetProperties();

		for (HProperty* Property : Properties)
		{
			if (Property == nullptr || Property->IsPrimitiveType()) continue;
			if (Property->IsGarbageCollectable() == false) continue;

			IGCObject* GCProperty = nullptr;

			if (Property->IsPointerType())
			{
				GCProperty = *Property->GetPtr<IGCObject*>(this);
			}
			else
			{
				GCProperty = Property->GetPtr<IGCObject>(this);
			}

			HCheck(GCProperty!= nullptr);
			OutList.push_back(GCProperty);
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
