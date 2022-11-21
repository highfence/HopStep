#include "Object.h"

namespace HopStep
{
	TArray<IGCObject*> HObject::GetGCProperties()
	{
		TArray<IGCObject*> Properties;

		return Properties;
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
