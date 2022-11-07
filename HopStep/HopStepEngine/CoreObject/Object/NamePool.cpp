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
		// Todo: very dangerous static_cast int64 hash to uint32. Must fix it.
		// Just generated uint32 type hash, or use it 64bit.
#pragma warning(disable: 4267)
		return static_cast<uint32>(Hash(InString));
#pragma warning(default: 4267)
	}

	const HNameEntry& HNamePool::FindEntry(uint32 Key)
	{
		HCheck(NameEntries.contains(Key));
		return NameEntries.find(Key)->second;
	}

	HNameEntry::HNameEntry(const HString& InValue)
		: Length(InValue.length())
	{
		HopStep::Core::Misc::HGenericMemory::MemSet((void*)Data, '\0', MaxNameLength * sizeof(HChar));
		HopStep::Core::Misc::HGenericMemory::MemCpy((void*)Data, (void*)InValue.c_str(), InValue.length() * sizeof(HChar));
	}

	void HNameEntry::GetName(HString& Out) const
	{
		Out = HString(Data);
	}
}

