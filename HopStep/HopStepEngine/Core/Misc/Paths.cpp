#include "Paths.h"

namespace HopStep
{
	HString HPaths::SolutionPath()
	{
		// Todo : consider source_location
		return HString(std::filesystem::current_path().parent_path()).append(TEXT("\\"));
	}

	HString HPaths::EnginePath()
	{
		return HString(SolutionPath().append(TEXT("HopStepEngine\\")));
	}

	HString HPaths::EngineConfigPath()
	{
		return L"";
	}

	HString HPaths::ShaderPath()
	{
		return EnginePath().append(TEXT("Runtime\\Render\\Shader\\"));
	}

	HString HPaths::ContentPath()
	{
		return SolutionPath().append(TEXT("Contents\\"));
	}
}
