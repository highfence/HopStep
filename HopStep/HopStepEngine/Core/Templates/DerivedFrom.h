#pragma once

#include "..\CoreStandardIncludes.h"

template <class TDerived, class TBase>
concept DerivedFrom = requires
{
	{ std::declval<TBase*&>() == std::declval<TDerived*&>() };
};