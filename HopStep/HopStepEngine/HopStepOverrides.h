#pragma once
#include "CoreStandardIncludes.h"

namespace HopStep
{
	using HChar = wchar_t;

	using HString = std::basic_string<wchar_t>;
	
	using HStringView = std::basic_string_view<wchar_t>;

	template <class ValueType>
	using TOptional = std::optional<ValueType>;
}
