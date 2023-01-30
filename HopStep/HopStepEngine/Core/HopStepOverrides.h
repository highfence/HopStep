#pragma once
#include "CoreStandardIncludes.h"

namespace HopStep
{
	/**
	 * Primitive type related overrides
	 */
	using HByte = std::byte;
	using HSize = std::size_t;
	using HAny = std::any;

	/**
	 * String type related overrides
	 */
	using HChar = wchar_t;
	using HString = std::basic_string<HChar>;
	using HStringView = std::basic_string_view<HChar>;
	using HStringStream = std::basic_stringstream<HChar>;

	/**
	 * Container type related overrides
	 */
	// Todo: replace this to TArray.
	template <class TValueType>
	using TArray = std::vector<TValueType>;

	template <typename TArgs>
	using TTuple = std::tuple<TArgs>;

	template <typename TKey, typename TValue>
	using TMap = std::unordered_map<TKey, TValue>;

	template <typename TValueType>
	using TStack = std::stack<TValueType>;

	/**
	 * Smart pointer type related overrides.
	 */
	template <class TType>
	using TUniquePtr = std::unique_ptr<TType>;

	template <class TType>
	using TSharedPtr = std::shared_ptr<TType>;

	template <class TType>
	using TWeakPtr = std::weak_ptr<TType>;

	/**
	 * Util type related overrides
	 */
	template <class TNumericType>
	using TNumericLimits = std::numeric_limits<TNumericType>;

	template <class TType>
	using TAtomic = std::atomic<TType>;

	template <class TValueType>
	using TOptional = std::optional<TValueType>;

	template <class THashType>
	using THash = std::hash<THashType>;
}
