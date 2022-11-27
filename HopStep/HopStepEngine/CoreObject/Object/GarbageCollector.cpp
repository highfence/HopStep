#include "..\..\Core\CoreExport.h"
#include "GarbageCollector.h"

namespace HopStep::Internal
{
	HGarbageCollector::HObjectCollection HGarbageCollector::ObjectCollection;
	HGarbageCollector::HSweepingCollection HGarbageCollector::SweepingCollections;

	void HGarbageCollector::Shutdown()
	{
		MarkAndSweep();
	}

	void HGarbageCollector::RegisterToGarbagePool(IGCObject* InObject)
	{
		HCheck(InObject && InObject->GetGCPoolIndex() == IGCObject::InvalidGCPoolIndex);

		uint32 ObjectIndex = IGCObject::InvalidGCPoolIndex;

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

		InObject->SetGCPoolIndex(ObjectIndex);
	}

	void HGarbageCollector::MarkAndSweep()
	{
		Mark();
		Sweep();
	}

	void HGarbageCollector::Mark()
	{
		SweepingCollections.MarkedObjects.clear();
		SweepingCollections.PendingIterateObjects.clear();

		TArray<IGCObject*>& ObjectArray = ObjectCollection.ObjectArray;

		// Finding Root Set
		for (IGCObject* GCObject : ObjectArray)
		{
			if (GCObject == nullptr || GCObject->IsGCRoot() == false) continue;

			GCObject->SetGCMark(true);
			SweepingCollections.MarkedObjects.emplace_back(GCObject);
		}

		while (true)
		{
			for (HSize Index = 0; Index < SweepingCollections.MarkedObjects.size(); ++Index)
			{
				IGCObject* MarkedObject = SweepingCollections.MarkedObjects[Index];

				TArray<IGCObject*> GCProperties = MarkedObject->GetGCProperties();

				for (IGCObject* GCProperty : GCProperties)
				{
					GCProperty->SetGCMark(true);
					SweepingCollections.PendingIterateObjects.emplace_back(GCProperty);
				}
			}

			if (SweepingCollections.PendingIterateObjects.empty())
			{
				break;
			}

			SweepingCollections.MarkedObjects.swap(SweepingCollections.PendingIterateObjects);
			SweepingCollections.PendingIterateObjects.clear();
		}
	}

	void HGarbageCollector::Sweep()
	{
		// Move unmarked object to remove list
		for (HSize Index = 0; Index < ObjectCollection.ObjectArray.size(); ++Index)
		{
			if (IGCObject* Ptr = ObjectCollection.ObjectArray[Index]; Ptr != nullptr)
			{
				if (Ptr->GetGCMark() == true)
				{
					Ptr->SetGCMark(false);
				}
				else
				{
					HCheck(Index == Ptr->GetGCPoolIndex());

					ObjectCollection.ObjectArray[Index] = nullptr;
					ObjectCollection.ObjectArrayEmptyIndexes.push(static_cast<uint32>(Index));
					ObjectCollection.PendingRemoveObjects.emplace_back(Ptr);
				}
			}
		}

		// Actual remove
		for (IGCObject* Ptr : ObjectCollection.PendingRemoveObjects)
		{
			delete Ptr;
		}

		ObjectCollection.PendingRemoveObjects.clear();
	}

	IGCObject* HGarbageCollector::GetGCObject(uint32 Index)
	{
		if (ObjectCollection.ObjectArray.size() <= Index)
		{
			return nullptr;
		}

		return ObjectCollection.ObjectArray[Index];
	}
}
