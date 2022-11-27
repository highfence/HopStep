#pragma once
#include "..\..\Core\HopStepOverrides.h"
#include "GCInterface.h"

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
		 * For debug & test. You should use MarkAndSweep() method instead of individual methods.
		 */
		static void Mark();

		/**
		 * For debug & test. You should use MarkAndSweep() method instead of individual methods.
		 */
		static void Sweep();

		static IGCObject* GetGCObject(uint32 Index);

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
