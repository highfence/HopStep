#include "pch.h"
#include "CppUnitTest.h"
#include "..\HopStepEngine\Core\Misc\Paths.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HopStepTest
{
	TEST_CLASS(CoreMiscTest)
	{
	public:
		
		TEST_METHOD(EngineDirectoryTest)
		{
			HopStep::HString EngineDir = HopStep::HPaths::EnginePath();

			std::wcout << EngineDir << std::endl;
		}
	};
}
