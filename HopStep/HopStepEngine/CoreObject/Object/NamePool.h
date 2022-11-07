#pragma once
#include "..\HopStepEngine\Core\HopStepCore.h"

namespace HopStep
{
	constexpr uint32 MaxNameLength = 1024u;
}

namespace HopStep::Internal
{
	/**
	 *
	 */
	struct HNameHash
	{
		

	};

	/**
	 *
	 */
	struct HNameValue
	{

	};

	/**
	 * 
	 */
	struct HNameEntry
	{
		explicit HNameEntry(const HString& InValue);

		/**
		 *
		 */
		void GetName(HString& Out) const;

		uint16 GetNameLength() const { return Length; }

	private:

		uint16 Length;
		HChar Data[MaxNameLength];
	};

	/**
	 * 
	 */
	class HNamePool
	{
	public:
		static HNamePool& GetNamePool()
		{
			// Todo: Removing singleton classes
			static HNamePool Instance;
			return Instance;
		}

		uint32 Store(const HString& InString);

		// Todo: Move to FNameValue's domain
		uint32 GenerateHash(const HString& InString);

		const HNameEntry& FindEntry(uint32 Key);

	private:

		// Todo: Divide this to NameShards
		TMap<uint32, HNameEntry> NameEntries;
	};
}