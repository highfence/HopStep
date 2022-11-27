#include "pch.h"
#include "CppUnitTest.h"
#include "..\HopStepEngine\CoreObject\Object\GarbageCollector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<> inline std::wstring ToString<::HopStep::HObject>(HObject* InObject)
	{
		return L"HObject";
	}
}

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

			// It should be the same for all other objects added to the root.
			HopStep::HObject* GCObject = HopStep::NewObject<HopStep::HObject>();
			RootObject->AddToRoot(GCObject);

			HopStep::Internal::HGarbageCollector::Mark();
			Assert::IsTrue(GCObject->GetGCMark());

			HopStep::Internal::HGarbageCollector::Sweep();
			Assert::IsTrue(HopStep::IsValidLowLevel(GCObject));
		}

		TEST_METHOD(GC_WeakObjectPtr)
		{
			HopStep::HObject* TransientObject = HopStep::NewObject<HopStep::HObject>();
			HopStep::TWeakObjectPtr<HObject> ObjectPtr = HopStep::MakeWeakObjectPtr(TransientObject);
			Assert::IsTrue(ObjectPtr.IsValid());
			Assert::AreEqual(TransientObject, ObjectPtr.Get());

			//HopStep::DoGarbageCollect();

			//Assert::IsFalse(ObjectPtr.IsValid());
		}
	};
}
