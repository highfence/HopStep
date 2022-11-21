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
			HopStep::HObject* ManagedObject = HopStep::NewObject<HopStep::HObject>();
			Assert::IsNotNull(ManagedObject);
			Assert::IsTrue(ManagedObject->GetPoolIndex() != HopStep::IGCObject::InvalidPoolIndex);

			if (ManagedObject != nullptr)
			{
				delete ManagedObject;
			}
		}
	};
}
