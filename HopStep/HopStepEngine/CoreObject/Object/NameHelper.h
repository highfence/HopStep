#pragma once
#include "..\HopStepEngine\Core\HopStepCore.h"

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

		explicit HNameEntry(uint32 InValue)
			: Id(InValue)
			, NameLength(0)
		{

		}

		bool IsValid() const
		{
			return Id.GetValue() != 0;
		}

	private:

		int32 NameLength;
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
				OutEntry = HNameEntry(1);
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
		};
	}
}