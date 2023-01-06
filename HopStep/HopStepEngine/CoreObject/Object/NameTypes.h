#pragma once
#include "..\HopStepEngine\Core\CoreExport.h"
#include "NameHelper.h"

namespace HopStep
{
	/**
	 * 
	 */
	class HName
	{
	public:

		/**
		 * 
		 */
		HName()
			: NameEntryKey()
			, Digits(HNAME_NO_DIGITS)
		{

		}

		/**
		 * 
		 */
		HName(const HString& NameString)
		{
			Internal::HNameHelper::MakeName(NameString, NameEntryKey, Digits);
		}

		/**
		 * 
		 */
		bool operator==(const HName& Other) const
		{
			return this->NameEntryKey == Other.NameEntryKey && this->GetDigits() == Other.GetDigits();
		}

		bool operator!=(const HName& Other) const
		{
			return !(*this == Other);
		}

		/**
		 * 
		 */
		uint32 GetDigits() const
		{
			return Digits;
		}

		/**
		 * 
		 */
		bool IsValid() const
		{
			return NameEntryKey.IsValid();
		}
		
		/**
		 * 
		 */
		HString ToString() const;

		uint64 GetHash() const
		{
			uint64 KeyValue = NameEntryKey.GetValue();
			return (KeyValue << 32) | Digits;
		}

	private:

		/**
		 * 
		 */
		HNameEntryId NameEntryKey;

		/**
		 * 
		 */
		uint32 Digits;
	};
}

#if !HopStep_On_CustomContainer
template<>
struct std::hash<HopStep::HName>
{
	std::size_t operator()(HopStep::HName const& InName) const noexcept
	{
		return std::size_t(InName.GetHash());
	}
};
#endif
