#include "pch.h"
#include "CppUnitTest.h"
#include "..\HopStepEngine\HopStep.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HopStepTest
{
	TEST_CLASS(HObjectTest)
	{
	public:
		TEST_CLASS_CLEANUP(HObject_ClassCleanUp)
		{
			HopStep::DoGarbageCollect();
		}

		TEST_METHOD(HObjectPtr_Valid)
		{
			HopStep::HObjectPtr ObjectPtr = HopStep::NewObject<HObject>();
			Assert::IsTrue(ObjectPtr);

			HopStep::HObjectPtr InValidPtr = nullptr;
			Assert::IsFalse(InValidPtr);
		}

		TEST_METHOD(TObjectPtr_Valid)
		{
			HopStep::TObjectPtr<HObject> ObjectPtr = HopStep::NewObject<HObject>();
			Assert::IsTrue(ObjectPtr);

			HopStep::TObjectPtr<HObject> InValidPtr = nullptr;
			Assert::IsFalse(InValidPtr);
		}
	};
}
