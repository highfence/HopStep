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

		TEST_METHOD(GC_NewObject)
		{
			HopStep::HObject* ManagedObject = HopStep::NewObject<HopStep::HObject>();
			Assert::IsNotNull(ManagedObject);
			Assert::IsTrue(ManagedObject->GetGCPoolIndex() != HopStep::IGCObject::InvalidGCPoolIndex);

			Assert::IsNotNull(ManagedObject->GetClass());
		}

		TEST_METHOD(GC_MarkAndSweep)
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

		TEST_METHOD(GC_RootObject)
		{
			HopStep::HRootSet* RootObject = HopStep::NewObject<HopStep::HRootSet>();
			Assert::IsNotNull(RootObject);
			Assert::IsTrue(RootObject->GetGCPoolIndex() != HopStep::IGCObject::InvalidGCPoolIndex);
			Assert::IsFalse(RootObject->GetGCMark());

			// If we invoke Mark(), RootObject must be marked.
			HopStep::Internal::HGarbageCollector::Mark();
			Assert::IsTrue(RootObject->GetGCMark());

			// After Sweep(), RootObject must be valid.
			HopStep::Internal::HGarbageCollector::Sweep();
			Assert::IsTrue(HopStep::IsValidLowLevel(RootObject));

			HopStep::HObject* GCObject = HopStep::NewObject<HopStep::HObject>();

		}

		TEST_METHOD(GC_Property_MarkAndSweep)
		{
			

		}
	};
}
