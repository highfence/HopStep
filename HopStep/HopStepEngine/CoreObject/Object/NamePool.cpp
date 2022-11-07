#include "NamePool.h"
#include "..\HopStepEngine\Core\HopStepCore.h"

namespace HopStep::Internal
{
	uint32 HNamePool::Store(const HString& InString)
	{
		uint32 Key = GenerateHash(InString);

		if (NameEntries.contains(Key))
		{
			return Key;
		}

		NameEntries.insert(std::make_pair(Key, InString));
		return Key;
	}

	uint32 HNamePool::GenerateHash(const HString& InString)
	{
		THash<HString> Hash{};
		return static_cast<uint32>(Hash(InString));
	}

	HString HNamePool::FindString(uint32 Key) const
	{
		return NameEntries.find(Key)->second;
	}
}

