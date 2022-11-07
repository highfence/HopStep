#include "NameTypes.h"

namespace HopStep
{
	HString HName::ToString() const 
	{
		HString Result;

		if (GetDigits() == HNAME_NO_DIGITS)
		{
			Result.reserve(NameEntry.GetNameLength());
			Result.append(NameEntry.GetString());
		}
		else
		{
			Result.reserve(NameEntry.GetNameLength() + 6);
			Result.append(NameEntry.GetString());
			Result.append(std::to_wstring(Digits));
		}

		return 	Result;
	}
}