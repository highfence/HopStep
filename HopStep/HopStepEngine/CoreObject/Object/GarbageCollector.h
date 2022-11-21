#pragma once
#include "..\..\Core\HopStepOverrides.h"
#include "GCInterface.h"
#include "CoreObjectConcepts.h"

namespace HopStep::Internal
{
	class HGarbageCollector
	{
	public:

		static void RegisterToGarbagePool(IGCObject* InObject);

	private:

		HGarbageCollector() = delete;

		struct HObjectCollection
		{
			TArray<IGCObject*> ObjectArray;
			TStack<uint32> ObjectArrayEmptyIndexes;
		};

		static HObjectCollection ObjectCollection;
	};
}

namespace HopStep
{
	/**
	 * Todo: Move to other places...
	 */
	template <class TType, typename... TArgs> requires GarbageCollectable<TType>
	TType* NewObject(TArgs... Params)
	{
		TType* NewObject = new TType(Params...);
		Internal::HGarbageCollector::RegisterToGarbagePool(NewObject);
		return NewObject;
	}
}