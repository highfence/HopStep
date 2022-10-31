#include "pch.h"
#include "CppUnitTest.h"
#include "../HopStepEngine/CoreObject/Reflection/Property.h"
#include "../HopStepEngine/CoreObject/Reflection/ReflectionTest.h"
#include "../HopStepEngine/CoreObject/Reflection/Class.h"
#include "../HopStepEngine/Core/HopStepOverrides.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	using HStructClass = ::HopStep::CoreObject::Reflection::HStruct;

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

			Assert::AreEqual((int32)3, *TestType->GetPropertyPtr<int32>(TestClass, L"A"));
			Assert::AreEqual(L'U', *TestType->GetPropertyPtr<HopStep::HChar>(TestClass, L"B"));
			Assert::IsTrue(*TestType->GetPropertyPtr<bool>(TestClass, L"C"));
			Assert::AreEqual(L"TestString", TestType->GetPropertyPtr<HopStep::HString>(TestClass, L"D")->c_str());
			Assert::IsNull(TestType->GetPropertyPtr<int32>(TestClass, L"WrongName"));

			delete TestClass;
		}

		TEST_METHOD(InnerClassAndPointerPropertyTest)
		{
			HReflectionTest* TestClass = new HReflectionTest();
			HClass* TestType = TestClass->StaticClass();

			// Initialize check
			HInnerClassTest** InnerPtr = TestType->GetPropertyPtr<HInnerClassTest*>(TestClass, L"InnerClassPtr");
			Assert::IsNull(*InnerPtr);

			// Pointer check
			HInnerClassTest* Ptr = new HInnerClassTest();
			TestClass->InnerClassPtr = Ptr;
			Assert::IsTrue(Ptr == *TestType->GetPropertyPtr<HInnerClassTest*>(TestClass, L"InnerClassPtr"));

			// Inner class check
			HClass* InnerType = HInnerClassTest::StaticClass();

			Ptr->InnerA = 3.5f;
			Ptr->InnerB = (uint8)4;
			Assert::IsTrue(abs(3.5f - *InnerType->GetPropertyPtr<float>(Ptr, L"InnerA")) < HopStep::TNumericLimits<float>::epsilon());
			Assert::AreEqual((int8)4, *InnerType->GetPropertyPtr<int8>(Ptr, L"InnerB"));

			delete Ptr;
			delete TestClass;
		}

		TEST_METHOD(StringPropertyTest)
		{
			HStringPropertyTest* TestClass = new HStringPropertyTest();
			HClass* TestType = HStringPropertyTest::StaticClass();

			TestClass->Post = L'B';
			Assert::AreEqual(L'B', *TestType->GetPropertyPtr<HopStep::HChar>(TestClass, L"Post"));

			TestClass->StringProperty = L"Test String... for extended";
			std::wstring* RealValue = TestType->GetPropertyPtr<HopStep::HString>(TestClass, L"StringProperty");
			Assert::AreEqual(L"Test String... for extended", RealValue->c_str());

			delete TestClass;
		}

		TEST_METHOD(ChangePropertValueTest)
		{
			HReflectionTest* TestClass = new HReflectionTest();
			HClass* TestType = HReflectionTest::StaticClass();

			TestType->ChangePropertyValue(TestClass, L"A", 99);
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

			Instance.ArrayProperty.push_back(3);
			Instance.ArrayProperty.push_back(4);
			Instance.ArrayProperty.push_back(-15);

			auto PropertyPtr = ArrayProperty->GetPtr<HopStep::HArray<int32>>(&Instance);
			Assert::AreEqual((int32)3, (int32)PropertyPtr->size());
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

				int32 AOffset = HopStep::CoreObject::Reflection::GetOffsetOf<TestStruct, int32>(&TestStruct::A);
				Assert::AreEqual((int32)0, AOffset);

				int32 BOffset = HopStep::CoreObject::Reflection::GetOffsetOf<TestStruct, void*>(&TestStruct::B);
				Assert::AreEqual((int32)8, BOffset);

				int32 COffset = HopStep::CoreObject::Reflection::GetOffsetOf<TestStruct, int32>(&TestStruct::C);
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

				int32 AOffset = HopStep::CoreObject::Reflection::GetOffsetOf<PackedTestStruct, int32>(&PackedTestStruct::A);
				Assert::AreEqual((int32)0, AOffset);

				int32 BOffset = HopStep::CoreObject::Reflection::GetOffsetOf<PackedTestStruct, void*>(&PackedTestStruct::B);
				Assert::AreEqual((int32)4, BOffset);

				int32 COffset = HopStep::CoreObject::Reflection::GetOffsetOf<PackedTestStruct, int32>(&PackedTestStruct::C);
				Assert::AreEqual((int32)12, COffset);
			}
		};
	};
}
