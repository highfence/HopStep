#include "pch.h"
#include "CppUnitTest.h"
#include "../HopStepEngine/CoreObject/Reflection/Property.h"
#include "../HopStepEngine/CoreObject/Reflection/PrimitiveProperty.h"
#include "../HopStepEngine/CoreObject/Reflection/ReflectionTest.h"
#include "../HopStepEngine/CoreObject/Reflection/Class.h"
#include "..\HopStepEngine\CoreObject\Reflection\Field.h"
#include "..\HopStepEngine\CoreObject\Object\ObjectGlobals.h"
#include "../HopStepEngine/Core/HopStepOverrides.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	using HStructClass = ::HopStep::HStruct;

	template<> inline std::wstring ToString<HStructClass>(HStructClass* InStruct)
	{
		return L"HStruct";
	}
}

namespace HopStepTest
{
	TEST_CLASS(ReflectionTest)
	{
	public:
		TEST_METHOD(StaticClassCreationTest)
		{
			HClass* ObjectType = HObject::StaticClass();
			Assert::IsNotNull(ObjectType);

			HopStep::HString ObjectName = L"HObject";
			Assert::AreEqual(ObjectName, ObjectType->GetName());
		}

		TEST_METHOD(GameTypeAccessTest)
		{
			HClass* GameType = HObject::StaticClass();
			Assert::IsNotNull(GameType);
		}

		TEST_METHOD(GameTypeNameTest)
		{
			HObject* GameObject = new HObject();

			HClass* GameType = HObject::StaticClass();
			Assert::AreEqual(GameObject->FriendlyName, HopStep::HStringView(GameType->GetName()));
			Assert::AreEqual(GameObject->FriendlyName, HopStep::HStringView(L"HObject"));

			delete GameObject;
		}

		TEST_METHOD(GetPropertyValueTest)
		{
			HReflectionTest* TestClass = new HReflectionTest();
			HClass* TestType = HReflectionTest::StaticClass();

			TestClass->A = 3;
			TestClass->B = 'U';
			TestClass->C = true;
			TestClass->D = L"TestString";

			Assert::AreEqual((int32)3, *TestType->FindProperty(L"A")->GetPtr<int32>(TestClass));
			Assert::AreEqual(L'U', *TestType->FindProperty(L"B")->GetPtr<HopStep::HChar>(TestClass));
			Assert::IsTrue(*TestType->FindProperty(L"C")->GetPtr<bool>(TestClass));
			Assert::AreEqual(L"TestString", TestType->FindProperty(L"D")->GetPtr<HopStep::HString>(TestClass)->c_str());
			Assert::IsNull(TestType->FindProperty(L"WrongName"));

			delete TestClass;
		}

		TEST_METHOD(InnerClassAndPointerPropertyTest)
		{
			HReflectionTest* TestClass = new HReflectionTest();
			HClass* TestType = TestClass->StaticClass();

			// Initialize check
			HInnerClassTest** InnerPtr = TestType->FindProperty(L"InnerClassPtr")->GetPtr<HInnerClassTest*>(TestClass);
			Assert::IsNull(*InnerPtr);

			// Pointer check
			HInnerClassTest* Ptr = new HInnerClassTest();
			TestClass->InnerClassPtr = Ptr;
			Assert::IsTrue(Ptr == *TestType->FindProperty(L"InnerClassPtr")->GetPtr<HInnerClassTest*>(TestClass));

			// Inner class check
			HClass* InnerType = HInnerClassTest::StaticClass();

			Ptr->InnerA = 3.5f;
			Ptr->InnerB = (uint8)4;
			Assert::IsTrue(abs(3.5f - *InnerType->FindProperty(L"InnerA")->GetPtr<float>(Ptr)) < HopStep::TNumericLimits<float>::epsilon());
			Assert::AreEqual((int8)4, *InnerType->FindProperty(L"InnerB")->GetPtr<int8>(Ptr));

			delete Ptr;
			delete TestClass;
		}

		TEST_METHOD(StringPropertyTest)
		{
			HStringPropertyTest* TestClass = new HStringPropertyTest();
			HClass* TestType = HStringPropertyTest::StaticClass();

			TestClass->Post = L'B';
			Assert::AreEqual(L'B', *TestType->FindProperty(L"Post")->GetPtr<HopStep::HChar>(TestClass));

			TestClass->StringProperty = L"Test String... for extended";
			std::wstring* RealValue = TestType->FindProperty(L"StringProperty")->GetPtr<HopStep::HString>(TestClass);
			Assert::AreEqual(L"Test String... for extended", RealValue->c_str());

			delete TestClass;
		}

		TEST_METHOD(ChangePropertValueTest)
		{
			HReflectionTest* TestClass = new HReflectionTest();
			HClass* TestType = HReflectionTest::StaticClass();

			TestType->FindProperty(L"A")->SetValue(TestClass, 99);
			Assert::AreEqual((int32)99, TestClass->A);

			delete TestClass;
		}

		TEST_METHOD(SuperClassTest)
		{
			HInheritanceTest* TestClass = new HInheritanceTest();
			HClass* TestType = TestClass->StaticClass();

			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(TestType->GetSuper()),
							 reinterpret_cast<std::uintptr_t>((HStruct*)HReflectionTest::StaticClass()));

			delete TestClass;
		}

		TEST_METHOD(ClassChildOfTest)
		{
			HClass* ObjectType = HObject::StaticClass();
			HClass* BaseType = HObjectBase::StaticClass();

			Assert::IsTrue(ObjectType->IsChildOf(BaseType));

			HClass* OtherType = HObjectInheritedTest::StaticClass();

			Assert::IsFalse(ObjectType->IsChildOf(OtherType));
		}

		TEST_METHOD(FunctionReflectionTest)
		{
			HFunctionTestObject Instance;
			HClass* Type = Instance.StaticClass();

			const HFunction* AddFunction = Type->FindFunction(L"Add");
			Assert::IsNotNull(AddFunction);

			int32 Result = AddFunction->Invoke<int32, int32, int32>((void*)(&Instance), 3, 7);
			Assert::AreEqual((int32)10, Result);

			Instance.B = -9;
			Instance.C = 15;

			const HFunction* AddBCFunction = Type->FindFunction(L"AddBC");
			Assert::IsNotNull(AddBCFunction);

			int32 ResultBC = AddBCFunction->Invoke<int32>((void*)(&Instance));
			Assert::AreEqual((int32)6, ResultBC);

			/*
			Instance.B = 11;
			Instance.C = -99;

			const HFunction* NoReturnFunction = Type->FindFunction(L"AddWithParamter");
			Assert::IsNotNull(NoReturnFunction);

			int32 ResultParam = 0;
			NoReturnFunction->Invoke<void, int32&>((void*)&Instance, ResultParam);
			Assert::AreEqual((int32)-88, ResultParam);
			*/
		}

		TEST_METHOD(HArrayPropertyReflectionTest)
		{
			HContainerReflectionTestObject Instance;
			HClass* Type = Instance.StaticClass();

			const HProperty* ArrayProperty = Type->FindProperty(L"ArrayProperty");
			Assert::IsNotNull(ArrayProperty);
			Assert::IsTrue(ArrayProperty->GetPropertyFlag(EPropertyFlag::ArrayProperty));

			Instance.ArrayProperty.push_back(3);
			Instance.ArrayProperty.push_back(4);
			Instance.ArrayProperty.push_back(-15);

			auto PropertyPtr = ArrayProperty->GetPtr<HopStep::TArray<int32>>(&Instance);
			Assert::AreEqual((int32)3, (int32)PropertyPtr->size());
		}

		TEST_METHOD(Reflection_PropertyOffset)
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
		}

		TEST_METHOD(Reflection_PropertyParam_GenerateTest)
		{
			auto Param = HopStep::Internal::HPropertyParamBase
			{
				.Name = TEXT("PropObject"),
				.Offset = HopStep::GetOffsetOf<HopStep::HObjectContainTestObject, HopStep::HObject*>(&HopStep::HObjectContainTestObject::PropObject),
				.ArrayDimension = 1,
				.Flags = (HopStep::Internal::EPropertyGenFlags)0x15,
				.Size = sizeof(HopStep::HObject*)
			};

			HopStep::HObjectContainTestObject NewObject;
			NewObject.PropObject = nullptr;

			HopStep::HObjectPtrProperty Property = HopStep::HObjectPtrProperty(Param);
			Assert::AreEqual(Property.GetName().ToString().c_str(), TEXT("PropObject"));

			HObject** Ptr = Property.GetPtr<HObject*>(&NewObject);
			Assert::AreEqual((intptr_t)Ptr, (intptr_t)&NewObject.PropObject);

			HObject* NullObject = *Ptr;
			Assert::IsNull(NullObject);
		}

		TEST_METHOD(OffsetTest)
		{
			struct TestStruct
			{
				int32 A;
				void* B;
				int32 C;
			};

			{
				Assert::AreEqual(24LLU, sizeof(TestStruct));

				int32 AOffset = HopStep::GetOffsetOf<TestStruct, int32>(&TestStruct::A);
				Assert::AreEqual((int32)0, AOffset);

				int32 BOffset = HopStep::GetOffsetOf<TestStruct, void*>(&TestStruct::B);
				Assert::AreEqual((int32)8, BOffset);

				int32 COffset = HopStep::GetOffsetOf<TestStruct, int32>(&TestStruct::C);
				Assert::AreEqual((int32)16, COffset);
			}

#pragma pack(push,	4)
			struct PackedTestStruct
			{
				int32 A;
				void* B;
				int32 C;
			};
#pragma pack(pop)

			{
				Assert::AreEqual(16LLU, sizeof(PackedTestStruct));

				int32 AOffset = HopStep::GetOffsetOf<PackedTestStruct, int32>(&PackedTestStruct::A);
				Assert::AreEqual((int32)0, AOffset);

				int32 BOffset = HopStep::GetOffsetOf<PackedTestStruct, void*>(&PackedTestStruct::B);
				Assert::AreEqual((int32)4, BOffset);

				int32 COffset = HopStep::GetOffsetOf<PackedTestStruct, int32>(&PackedTestStruct::C);
				Assert::AreEqual((int32)12, COffset);
			}
		};
	};
}
