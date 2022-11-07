#pragma once
#include "..\HopStepEngine\Core\HopStepCore.h"
#include "NamePool.h"

namespace HopStep
{
#define HNAME_NO_DIGITS 0

	struct HNameEntryId
	{
		HNameEntryId() = default;
		HNameEntryId(uint32 InValue) : Value(InValue) {};

		uint32 GetValue() const { return Value; }

	private:

		uint32 Value;
	};

	/**
	 * Hide NamePool implementation from who using HName.
	 */
	struct HNameEntry
	{
		HNameEntry()
			: Id()
			, NameLength(0)
		{

		}

		explicit HNameEntry(uint32 InValue, uint32 InLength)
			: Id(InValue)
			, NameLength(InLength)
		{

		}

		bool IsValid() const
		{
			return Id.GetValue() != 0;
		}

		uint32 GetNameLength() const { return NameLength; }

		HString GetString() const;

	private:

		uint32 NameLength;
		// Todo: Don't store name string to pool. Handle with HNameEntry self.
		HNameEntryId Id;
	};

	namespace Internal
	{
		/**
		 *
		 */
		class HNameHelper
		{
		public:

			/**
			 *
			 */
			static void MakeName(const HString& NameString, HNameEntry& OutEntry, uint32& OutDigits)
			{
				if (NameString.empty())
				{
					OutEntry = HNameEntry();
					OutDigits = HNAME_NO_DIGITS;
					return;
				}

				uint32 TrailingDigit = 0;
				uint32 TrailingDigitLength = 0;

				DetectTrailingDigitFromString(NameString, TrailingDigit, TrailingDigitLength);

				OutDigits = TrailingDigit;
				RegistEntryToPool(NameString.substr(0, NameString.length() - TrailingDigitLength), OutEntry);
			}

			static int64 Atoi64(const HChar* Str, int32 Length)
			{
				int64 Result = 0;

				for (int32 Index = 0; Index < Length; ++Index)
				{
					Result = 10 * Result + Str[Index] - '0';
				}

				return Result;
			}

			static void DetectTrailingDigitFromString(const HString& NameString, uint32& Digit, uint32& DigitStringLength)
			{
				for (int32 Index = static_cast<int32>(NameString.length() - 1); Index >= 0; --Index)
				{
					HChar TrailingCharacter = NameString[Index];
					if (TrailingCharacter < '0' || TrailingCharacter > '9')
					{
						break;
					}

					++DigitStringLength;
				}

				if (DigitStringLength > 0)
				{
					Digit = static_cast<uint32>(Atoi64(&NameString[NameString.length() - DigitStringLength], DigitStringLength));
				}
			}

		private:

			static void RegistEntryToPool(const HString& RawName, HNameEntry& OutEntry)
			{
				HNamePool& NamePool = HNamePool::GetNamePool();

				uint32 Id = NamePool.Store(RawName);
				OutEntry = HNameEntry(Id, RawName.length());
			}
		};
	}
}