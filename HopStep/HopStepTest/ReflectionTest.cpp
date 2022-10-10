#include "pch.h"
#include "CppUnitTest.h"
#include "../HopStepEngine/CoreObject/Reflection/Property.h"
#include "../HopStepEngine/CoreObject/Reflection/ReflectionTest.h"
#include "../HopStepEngine/Core/HopStepOverrides.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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
			Assert::AreEqual(GameObject->FriendlyName, std::wstring_view(GameType->GetName()));
			Assert::AreEqual(GameObject->FriendlyName, std::wstring_view(L"HObject"));

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
			Assert::IsTrue((3.5f - *InnerType->GetPropertyPtr<float>(Ptr, L"InnerA")) < std::numeric_limits<float>::epsilon());
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

		TEST_METHOD(PropertyClipboradSerializeTest)
		{

		};
	};
}
