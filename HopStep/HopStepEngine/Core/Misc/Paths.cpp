#include "Paths.h"

namespace HopStep
{
	HString HPaths::EnginePath()
	{
		// Todo : consider source_location
		return HString(std::filesystem::current_path()
			.parent_path() // Core
			.append(L"HopStepEngine"));
	}

	HString HPaths::EngineConfigPath()
	{
		return L"";
	}

	HString HPaths::ShaderPath()
	{
		return EnginePath().append(TEXT("\\Runtime\\Render\\Shader"));
	}
}
