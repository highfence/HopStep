#pragma once
#include "../HopStepCore.h"

namespace HopStep::Paths
{
	HString EnginePath()
	{
		// Todo : consider source_location
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
