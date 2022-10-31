#pragma once
#include "..\CoreStandardIncludes.h"
#include "IDelegateInstance.h"

using DelegateInstanceInterface = HopStep::Core::Delegates::IDelegateInstance;

template <class TDelegatePolicyType>
concept DelegatePolicy = requires
{

	/**
	 * 
	 */
	TDelegatePolicyType::HDelegateInstancePolicy;

	/**
	 * 
	 */
	TDelegatePolicyType::HDelegateBasePolicy;	

	// Todo : I want to constraint that policy must be inherited from base classes. Like under line.
	// requires std::is_base_of<DelegateInstanceInterface, TDelegatePolicyType::HDelegateBasePolicy>::Value;
};
