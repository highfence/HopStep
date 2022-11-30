// #include "..\Reflection\Property.h"
#include "Object.h"

namespace HopStep
{
	void HObject::GetGCProperties(TArray<IGCObject*>& OutList) 
	{
		if (bGCPropertyCached == false)
		{
			HClass* ThisClass = GetClass();

			const TArray<HProperty*> Properties = ThisClass->GetProperties();

			for (const HProperty* Property : Properties)
			{
				if (Property == nullptr || Property->IsPrimitiveType()) continue;

				if (Property->IsGarbageCollectable())
				{
					HObjectBase* Parent = reinterpret_cast<HObjectBase*>(this);
					IGCObject* GCObject = *Property->GetPtr<IGCObject*>(Parent);
					CachedGCProperties.emplace_back(GCObject);
				}
			}
		}

		OutList.append_range(CachedGCProperties);
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
