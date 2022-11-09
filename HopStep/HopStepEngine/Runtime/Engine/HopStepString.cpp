#include "HopStepString.h"

namespace HopStep
{
	void HStringOutputDevice::Serialize(const HChar* InValue, LogType Verbosity, const HName& Catergory)
	{
		Value += InValue;
	}
}