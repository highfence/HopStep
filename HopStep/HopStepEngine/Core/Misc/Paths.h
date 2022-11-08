#pragma once
#include "../CoreExport.h"

namespace HopStep
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
