#pragma once
#include "..\..\Core\HopStepOverrides.h"
#include "GCInterface.h"
#include "CoreObjectConcepts.h"
#include "GarbageCollector.h"


namespace HopStep
{
	template <typename TType>
	void SetClassPrivate(TType* NewInstance);

	template <typename TType> requires std::derived_from<TType, HObjectBase>
	void SetClassPrivate(TType* NewInstance)
	{
		NewInstance->SetClass(TType::StaticClass());
	}

	/**
	 * Todo: Move to other places...
	 */
	template <class TType, typename... TArgs> requires GarbageCollectable<TType>
	TType* NewObject(TArgs... Params)
	{
		TType* NewObject = new TType(Params...);
		SetClassPrivate(NewObject);
		Internal::HGarbageCollector::RegisterToGarbagePool(NewObject);
		return NewObject;
	}

	/**
	 * Todo: Move to other places...
	 */
	void DoGarbageCollect();

	/**
	 * Todo: Move to other places...
	 */
	bool IsValidLowLevel(IGCObject* Object);
}