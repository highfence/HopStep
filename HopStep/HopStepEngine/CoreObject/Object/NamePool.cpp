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
		// Todo: very dangerous static_cast int64 hash to uint32. Must fix it.
		// Just generated uint32 type hash, or use it 64bit.
#pragma warning(disable: 4267)
		return static_cast<uint32>(Hash(InString));
#pragma warning(default: 4267)
	}

	HString HNamePool::FindString(uint32 Key) const
	{
		return NameEntries.find(Key)->second;
	}
}

