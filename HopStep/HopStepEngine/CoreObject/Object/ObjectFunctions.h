#pragma once
#include "..\..\Core\HopStepOverrides.h"
#include "GCInterface.h"
#include "CoreObjectConcepts.h"
#include "GarbageCollector.h"

namespace HopStep::Internal
{
	template <typename TType>
	void SetClassPrivate(TType* NewInstance);

	template <typename TType> requires std::derived_from<TType, HObjectBase>
	void SetClassPrivate(TType* NewInstance)
	{
		NewInstance->SetClass(TType::StaticClass());
	}
}

namespace HopStep
{
	/**
	 * 	
	 */
	template <class TType, typename... TArgs> requires GarbageCollectable<TType>
	TType* NewObject(TArgs... Params)
	{
		TType* NewObject = new TType(Params...);
		Internal::SetClassPrivate(NewObject);
		Internal::HGarbageCollector::RegisterToGarbagePool(NewObject);
		return NewObject;
	}

	/**
	 * 
	 */
	void DoGarbageCollect();

	/**
	 * 
	 */
	bool IsValidLowLevel(IGCObject* Object);
}