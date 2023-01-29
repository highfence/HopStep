#pragma once
#include "RemoveReference.h"
#include "RemoveConst.h"
#include "..\PrimitiveTypeDefines.h"

/**
 * Implement std::forward
 * When reference type comes, just return with r-value reference.
 */
template <typename TType>
TType&& Forward(typename TRemoveReference<TType>::Type& Obj)
{
	return (TType&&)Obj;
}

template <typename TType>
TType&& Forward(typename TRemoveReference<TType>::Type&& Obj)
{
	return (TType&&)Obj;
}

template <typename TComObject, HopStep::HSize N>
char (&HopStepArraySizeHelper(const TComObject(&InputArray)[N]))[N];

/**
 * Return size of input array.
 */
#define HOPSTEP_ARRAY_COUNT(array) (sizeof(HopStepArraySizeHelper(array)))
