#pragma once
#include "DelegateConcepts.h"
#include "IDelegateInstance.h"

namespace HopStep::Core::Delegates
{
	class HDelegateBase
	{
	public:

	};

	struct HDefaultDelegatePolicy
	{
		using HDelegateInstancePolicy = IDelegateInstance;
		using HDelegateBasePolicy = HDelegateBase;
	};

	template <typename TDelegatePolicyType> requires DelegatePolicy<TDelegatePolicyType>
	class TDelegateBase : public TDelegatePolicyType::HDelegateBasePolicy
	{
	public:

	};
}