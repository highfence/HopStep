#pragma once
#include "..\..\Core\HopStepOverrides.h"
#include "..\..\CoreObject\Object\ObjectBase.h"
#include "GCInterface.h"
#include "GarbageCollector.h"

namespace HopStep::Internal
{
	template <typename TType>
	void SetClassPrivate(TType* NewInstance);

	template <typename TType> requires std::derived_from<TType, HObjectBase>
	void SetClassPrivate(TType* NewInstance)
	{
		HClass* TypeClass = TType::StaticClass();
		HCheck(TypeClass != nullptr);
		HCheck(TypeClass->GetName().length() > 0 && TypeClass->GetName().length() < 1024);

		NewInstance->SetClass(TypeClass);
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