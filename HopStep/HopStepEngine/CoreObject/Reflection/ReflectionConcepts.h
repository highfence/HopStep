#pragma once
#include "Core\CoreStandardIncludes.h"

namespace HopStep::CoreObject::Reflection
{
	class HProperty;
}

template <class TType>
concept StaticClassGetable = requires
{
	TType::StaticClass();
};

template <class TType>
concept HPropertyDerived = std::derived_from<TType, HopStep::CoreObject::Reflection::HProperty>;


