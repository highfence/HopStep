#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HopStepTest
{
	TEST_CLASS(CoreGCTest)
	{
	public:

		TEST_METHOD(GCNewTest)
		{
			HopStep::HObject* NewObject = HopStep::NewObject<HopStep::HObject>();
			Assert::IsNotNull(NewObject);
		}
	};
}
