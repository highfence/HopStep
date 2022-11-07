#pragma once
#include "..\HopStepEngine\Core\HopStepCore.h"

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

		// Todo: Remove this.
		HString FindString(uint32 Key) const;

	private:

		// Todo: Divide this to NameShards
		TMap<uint32, HString> NameEntries;
	};
}