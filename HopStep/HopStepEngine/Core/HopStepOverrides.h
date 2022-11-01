#pragma once
#include "CoreStandardIncludes.h"

namespace HopStep
{
	using HChar = wchar_t;

	using HString = std::basic_string<HChar>;
	
	using HStringView = std::basic_string_view<HChar>;

	using HStringStream = std::basic_stringstream<HChar>;

	template <class TValueType>
	using TOptional = std::optional<TValueType>;

	template <class TValueType>
	using HArray = std::vector<TValueType>;

	template <class TType>
	using HUniquePtr = std::unique_ptr<TType>;

	using HByte = std::byte;

	using HAny = std::any;

	using HSize = std::size_t;

	template <class TNumericType>
	using TNumericLimits = std::numeric_limits<TNumericType>;

	template <class TType>
	using TAtomic = std::atomic<TType>;

	template <typename TArgs>
	using TTuple = std::tuple<TArgs>;

}
