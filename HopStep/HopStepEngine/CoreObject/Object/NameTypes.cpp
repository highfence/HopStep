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

		return 	Result;
	}
}