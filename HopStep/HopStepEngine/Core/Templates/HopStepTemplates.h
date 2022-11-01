#pragma once
#include "RemoveReference.h"

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