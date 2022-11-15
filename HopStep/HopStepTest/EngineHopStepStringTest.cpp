#include "pch.h"
#include "CppUnitTest.h"
#include "..\HopStepEngine\HopStep.h"
#include "..\HopStepEngine\Runtime\Engine\HopStepString.h"
#include "..\HopStepEngine\Runtime\Engine\Exporter.h"
#include "..\HopStepEngine\CoreObject\Reflection\ReflectionTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HopStepTest
{
	TEST_CLASS(HopStepStringTest)
	{
	public:

		TEST_METHOD(StringOutputDevice_Test_Serialize)
		{
			HopStep::HStringOutputDevice Device;
			HopStep::HObjectDerivedTestObject Object;
			HopStep::HExporter::ExportToOutputDevice(&Device, &Object);

			const HString& ObjectString = Device.GetValue();
			Assert::IsFalse(ObjectString.empty());
		}
	};
}