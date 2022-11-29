#include "pch.h"
#include "CppUnitTest.h"
#include "..\HopStepEngine\CoreObject\Object\GarbageCollector.h"
#include "..\HopStepEngine\CoreObject\Reflection\ReflectionTest.h"

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
			HopStep::Internal::HGarbageCollector::Shutdown();
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

			HopStep::DoGarbageCollect();
			Assert::IsFalse(ObjectPtr.IsValid());
		}

		TEST_METHOD(GC_HPropertyLifeTime)
		{
			std::wostringstream os;
			os << TEXT("sizeof(HObjectContainTestObject) is ") << sizeof(HObjectContainTestObject) << "\n";
			os << TEXT("sizeof(HObject) is ") << sizeof(HObject) << "\n";
			os << TEXT("sizeof(HObjectBase) is ") << sizeof(HObjectBase) << "\n";

			HopStep::HObjectContainTestObject ContainObject;
			HopStep::HObject PropObjectInStack;
			ContainObject.PropObject = &PropObjectInStack;

			os << TEXT("ContainObject address : ") << (uintptr_t)&ContainObject << "\n";
			os << TEXT("PropObject address : ") << (uintptr_t)&PropObjectInStack << "\n";
			os << TEXT("ContainObject.PropObject address : ") << (uintptr_t)&(ContainObject.PropObject) << "\n";

			void* ObjectPtr = &ContainObject;
			Assert::AreEqual((uintptr_t)&ContainObject, (uintptr_t)ObjectPtr);
			HObject** GetPtrResult = (HObject**)((char*)ObjectPtr + 80);

			os << TEXT("GetPtrResult address : ") << (uintptr_t)GetPtrResult << "\n";
			uintptr_t GetPtrIntPtr = (uintptr_t)GetPtrResult;
			auto Offset = GetPtrIntPtr - (uintptr_t)&ContainObject;

			os << TEXT("GetPtrResult - ContainObject : ") << Offset << "\n";
			os << TEXT("dereferencing GetPtrResult : ") << (uintptr_t)*GetPtrResult << "\n";

			Logger::WriteMessage(os.str().c_str());

			//HopStep::HRootSet* RootSet = HopStep::NewObject<HopStep::HRootSet>();
			//HopStep::HObjectContainTestObject* OwnerObject = HopStep::NewObject<HopStep::HObjectContainTestObject>();
			//OwnerObject->PropObject = HopStep::NewObject<HopStep::HObject>();
			//RootSet->AddToRoot(OwnerObject);

			//// If we invoke Mark(), All object must be marked.
			//HopStep::Internal::HGarbageCollector::Mark();
			//Assert::IsTrue(RootSet->GetGCMark());
			//Assert::IsTrue(OwnerObject->GetGCMark());
			//Assert::IsTrue(OwnerObject->PropObject->GetGCMark());

			//HopStep::Internal::HGarbageCollector::Sweep();
		}
	};
}
