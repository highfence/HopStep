// #include "..\Reflection\Property.h"
#include "Object.h"

namespace HopStep
{
	void HObject::GetGCProperties(TArray<IGCObject*>& OutList) 
	{

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
