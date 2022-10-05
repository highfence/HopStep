#pragma once
#include "Core\CoreStandardIncludes.h"

namespace HopStep::CoreObject::Reflection
{
	class HProperty;
}

template <class TType>
concept StaticClassGetable = requires(TType Type)
{
	TType::StaticClass();
};

template <class TType>
concept HPropertyDerived = requires(TType Type)
{
	requires std::derived_from<TType, HopStep::CoreObject::Reflection::HProperty>;
};
