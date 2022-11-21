#include "pch.h"
#include "CppUnitTest.h"
#include "..\HopStepEngine\CoreObject\Object\GarbageCollector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HopStepTest
{
	TEST_CLASS(CoreGCTest)
	{
	public:

		TEST_METHOD_CLEANUP(CleanUp)
		{
			HopStep::DoGarbageCollect();
		}

		TEST_METHOD(GCNewTest)
		{
			HopStep::HObject* ManagedObject = HopStep::NewObject<HopStep::HObject>();
			Assert::IsNotNull(ManagedObject);
			Assert::IsTrue(ManagedObject->GetGCPoolIndex() != HopStep::IGCObject::InvalidGCPoolIndex);

			Assert::IsNotNull(ManagedObject->GetClass());
		}

		TEST_METHOD(GCSweepTest)
		{
			HopStep::HObject* TransientObject = HopStep::NewObject<HopStep::HObject>();
			Assert::IsNotNull(TransientObject);
			Assert::IsTrue(TransientObject->GetGCPoolIndex() != HopStep::IGCObject::InvalidGCPoolIndex);
			Assert::IsFalse(TransientObject->GetGCMark());

			int32 PoolIndex = TransientObject->GetGCPoolIndex();

			HopStep::Internal::HGarbageCollector::Mark();
			Assert::IsFalse(TransientObject->GetGCMark());

			HopStep::Internal::HGarbageCollector::Sweep();

			HopStep::HObject* OtherObjet = HopStep::NewObject<HopStep::HObject>();
			Assert::IsTrue(OtherObjet->GetGCPoolIndex() == PoolIndex);
		}
	};
}
