#pragma once
#include "..\HopStepEngine\Core\HopStepCore.h"
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
			: NameEntry()
			, Digits(HNAME_NO_DIGITS)
		{

		}

		/**
		 * 
		 */
		HName(const HString& NameString)
		{
			Internal::HNameHelper::MakeName(NameString, NameEntry, Digits);
		}

		/**
		 * 
		 */
		HNameEntry GetEntry() const
		{
			return NameEntry;
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
			return NameEntry.IsValid();
		}
		
		/**
		 * 
		 */
		HString ToString() const;

	private:

		HNameEntry NameEntry;
		uint32 Digits;
	};
}