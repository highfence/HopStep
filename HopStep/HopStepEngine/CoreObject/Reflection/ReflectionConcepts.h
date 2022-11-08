#pragma once
#include "Core\CoreStandardIncludes.h"

namespace HopStep
{
	class HProperty;
}

template <class TType>
concept StaticClassGetable = requires
{
	TType::StaticClass();
};

template <class TType>
concept HPropertyDerived = std::derived_from<TType, HopStep::HProperty>;


