#pragma once
#include "..\HopStepEngine\Core\PrimitiveTypeDefines.h"
#include "..\HopStepEngine\Core\HopStepOverrides.h"

#define HNAME_NO_DIGITS 0

namespace HopStep
{
	struct HNameEntryId
	{
		HNameEntryId() = default;
		HNameEntryId(uint32 InValue) : Value(InValue) {};

	private:

		uint32 Value;
	};

	/**
	 * 
	 */
	struct HNameEntry
	{



	private:

		int32 NameLength;
		HNameEntryId Id;

	};

	namespace Internal
	{
		int64 Atoi64(const HChar* Str, int32 Length)
		{
			int64 Result = 0;

			for (int32 Index = 0; Index < Length; ++Index)
			{
				Result = 10 * Result + Str[Index] - '0';
			}

			return Result;
		}

		void DetectTrailingDigitFromString(const HString& NameString, uint32& Digit, uint32& DigitStringLength)
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

		void MakeName(const HString& NameString, HNameEntry& OutEntry, uint32& OutDigits)
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
		}
	}

	/**
	 * 
	 */
	class HName
	{
	public:

		HName()
			: NameEntry()
			, Digits(HNAME_NO_DIGITS)
		{

		}

		HName(const HString& NameString)
		{
			Internal::MakeName(NameString, NameEntry, Digits);
		}


		HNameEntry GetEntry() const
		{
			return NameEntry;
		}

		uint32 GetDigits() const
		{
			return Digits;
		}

		bool IsValid() const
		{
			return NameEntry.
		}

	private:

		HNameEntry NameEntry;
		uint32 Digits;
	};
}