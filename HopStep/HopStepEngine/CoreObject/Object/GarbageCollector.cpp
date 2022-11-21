#include "..\..\Core\CoreExport.h"
#include "GarbageCollector.h"

namespace HopStep::Internal
{
	HGarbageCollector::HObjectCollection HGarbageCollector::ObjectCollection;

	void HGarbageCollector::RegisterToGarbagePool(IGCObject* InObject)
	{
		HCheck(InObject && InObject->GetPoolIndex() == IGCObject::InvalidPoolIndex);

		uint32 ObjectIndex = IGCObject::InvalidPoolIndex;

		if (ObjectCollection.ObjectArrayEmptyIndexes.empty() == false)
		{
			ObjectIndex = ObjectCollection.ObjectArrayEmptyIndexes.top();
			ObjectCollection.ObjectArrayEmptyIndexes.pop();
			ObjectCollection.ObjectArray[ObjectIndex] = InObject;
		}
		else
		{
			ObjectIndex = (uint32)(ObjectCollection.ObjectArray.size());
			ObjectCollection.ObjectArray.emplace_back(InObject);
		}

		InObject->SetPoolIndex(ObjectIndex);
	}
}