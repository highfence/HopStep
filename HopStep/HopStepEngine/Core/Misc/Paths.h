#pragma once
#include "../HopStepCore.h"

namespace HopStep::Paths
{
	HString EnginePath()
	{
		return HString(std::filesystem::current_path()
			.parent_path()
			.parent_path()
			.append(L"HopStepEngine"));
	}

	HString EngineConfigPath() 
	{
		return L"";
	}
}
