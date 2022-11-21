#pragma once
#include "GCInterface.h"
#include "CoreObjectConcepts.h"

namespace HopStep
{
	template <class TType> requires GarbageCollectable<TType>
	TType* NewObject()
	{
		return nullptr;
	}
}