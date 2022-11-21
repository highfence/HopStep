#pragma once
#include "..\..\Core\HopStepOverrides.h"
#include "GCInterface.h"
#include "ObjectBase.h"
#include "CoreObjectConcepts.h"

namespace HopStep::Internal
{
	/**
	 * 
	 */
	class HGarbageCollector
	{
	public:

		/**
		 * 
		 */
		static void Shutdown();

		/**
		 * 
		 */
		static void RegisterToGarbagePool(IGCObject* InObject);

		/**
		 * 
		 */
		static void MarkAndSweep();

		/**
		 * 
		 */
		static void Mark();

		/**
		 * 
		 */
		static void Sweep();

	private:

		HGarbageCollector() = delete;

		struct HObjectCollection
		{
			TArray<IGCObject*> ObjectArray;
			TArray<IGCObject*> PendingRemoveObjects;
			TStack<uint32> ObjectArrayEmptyIndexes;
		};

		static HObjectCollection ObjectCollection;

		struct HSweepingCollection
		{
			TArray<IGCObject*> MarkedObjects;
			TArray<IGCObject*> PendingIterateObjects;
		};

		static HSweepingCollection SweepingCollections;
	};
}
