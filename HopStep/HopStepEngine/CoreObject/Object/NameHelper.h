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

		bool IsValid() const { return Value != 0; }

		bool operator==(const HNameEntryId& Other) const
		{
			return this->GetValue() == Other.GetValue();
		}

	private:

		uint32 Value;
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
			static HString GetNameString(const HNameEntryId& EntryKey, uint32 Digit)
			{
				HNamePool& NamePool = HNamePool::GetNamePool();
				
				const HNameEntry& Entry = NamePool.FindEntry(EntryKey.GetValue());

				HString Result;
				Entry.GetName(Result);

				if (Digit != 0)
				{
					Result.append(std::to_wstring(Digit));
				}

				return Result;
			}

			/**
			 *
			 */
			static void MakeName(const HString& NameString, HNameEntryId& OutEntryKey, uint32& OutDigits)
			{
				if (NameString.empty())
				{
					OutEntryKey = HNameEntryId();
					OutDigits = HNAME_NO_DIGITS;
					return;
				}

				uint32 TrailingDigit = 0;
				uint32 TrailingDigitLength = 0;

				DetectTrailingDigitFromString(NameString, TrailingDigit, TrailingDigitLength);

				OutDigits = TrailingDigit;
				RegistEntryToPool(NameString.substr(0, NameString.length() - TrailingDigitLength), OutEntryKey);
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

			static void RegistEntryToPool(const HString& RawName, HNameEntryId& OutEntryKey)
			{
				HNamePool& NamePool = HNamePool::GetNamePool();
// todo : remove this pragma warning
#pragma warning(disable: 4267)
				uint32 Id = NamePool.Store(RawName);
				OutEntryKey = HNameEntryId(Id);
#pragma warning(default: 4267)
			}
		};
	}
}