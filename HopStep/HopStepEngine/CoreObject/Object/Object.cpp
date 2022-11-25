// #include "..\Reflection\Property.h"
#include "Object.h"

namespace HopStep
{
	TArray<IGCObject*> HObject::GetGCProperties()
	{
		TArray<IGCObject*> GCProperties;

		HClass* ThisClass = GetClass();

		//const TArray<HProperty*> Properties = ThisClass->GetProperties();

		//for (const HProperty* Property : Properties)
		//{

		//}

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
}
