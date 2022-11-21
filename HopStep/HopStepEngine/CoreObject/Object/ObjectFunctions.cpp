#include "ObjectFunctions.h"

namespace HopStep
{
	void DoGarbageCollect()
	{
		Internal::HGarbageCollector::MarkAndSweep();
	}

	bool IsValidLowLevel(IGCObject* Object)
	{
		if (Object == nullptr || Object->GetGCPoolIndex() == IGCObject::InvalidGCPoolIndex)
		{
			return false;
		}

		return true;
	}
}