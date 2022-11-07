#include "NameTypes.h"

namespace HopStep
{
	HString HName::ToString() const 
	{
		return Internal::HNameHelper::GetNameString(NameEntryKey, GetDigits());
	}
}