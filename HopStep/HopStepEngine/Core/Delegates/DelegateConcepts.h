#pragma once
#include "..\CoreStandardIncludes.h"
#include "IDelegateInstance.h"

using DelegateInstanceInterface = HopStep::IDelegateInstance;

template <class TDelegatePolicyType>
concept DelegatePolicy = requires
{
	requires sizeof(TDelegatePolicyType) != 0;

	/**
	 * 
	 */
	// TDelegatePolicyType::HDelegateInstancePolicy;

	/**
	 * 
	 */
	// TDelegatePolicyType::HDelegateBasePolicy;	

	// Todo : I want to constraint that policy must be inherited from base classes. Like under line.
	// requires std::is_base_of<DelegateInstanceInterface, TDelegatePolicyType::HDelegateBasePolicy>::Value;
};
