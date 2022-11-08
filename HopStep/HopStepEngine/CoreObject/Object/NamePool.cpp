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

		HNameEntry Entry = HNameEntry(InString);
		NameEntries.insert(std::make_pair(Key, Entry));
		return Key;
	}

	uint32 HNamePool::GenerateHash(const HString& InString)
	{
		THash<HString> Hash{};
		// Todo: use upper 32 bit to determine shard index. and lower 32bit to hash.
		return static_cast<uint32>(Hash(InString));
	}

	const HNameEntry& HNamePool::FindEntry(uint32 Key)
	{
		HCheck(NameEntries.contains(Key));
		return NameEntries.find(Key)->second;
	}

	HNameEntry::HNameEntry(const HString& InValue)
		: Length(static_cast<uint16>(InValue.length()))
	{
		HopStep::Core::Misc::HGenericMemory::MemSet((void*)Data, '\0', MaxNameLength * sizeof(HChar));
		HopStep::Core::Misc::HGenericMemory::MemCpy((void*)Data, (void*)InValue.c_str(), InValue.length() * sizeof(HChar));
	}

	void HNameEntry::GetName(HString& Out) const
	{
		Out = HString(Data);
	}
}

