// #include "..\Reflection\Property.h"
#include "Object.h"

namespace HopStep
{
	TArray<IGCObject*> HObject::GetGCProperties()
	{
		TArray<IGCObject*> GCProperties;

		HClass* ThisClass = GetClass();

		const TArray<HProperty*> Properties = ThisClass->GetProperties();

		for (const HProperty* Property : Properties)
		{
			if (Property == nullptr || Property->IsPrimitiveType()) continue;

			if (Property->IsGarbageCollectable())
			{
				HObjectBase* Parent = dynamic_cast<HObjectBase*>(this);
				IGCObject* GCObject = Property->GetPtr<IGCObject>(Parent);
				GCProperties.emplace_back(GCObject);
			}
		}

		return GCProperties;
	}

	bool HObject::IsGCRoot() const
	{
		return false;
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
