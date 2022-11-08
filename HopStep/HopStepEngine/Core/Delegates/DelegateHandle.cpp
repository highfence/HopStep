#include "..\HopStepOverrides.h"
#include "DelegateHandle.h"

using namespace HopStep;

namespace Internal
{
	::HopStep::TAtomic<uint64> NextIDGenerator;
}

uint64 HDelegateHandle::GenerateNewID()
{
	uint64 Result = ++Internal::NextIDGenerator;

	if (Result == 0LL)
	{
		Result = ++Internal::NextIDGenerator;
	}

	return Result;
}
