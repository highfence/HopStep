#include "pch.h"
#include "CppUnitTest.h"
#include "../HopStepEngine/CoreObject/Reflection/Property.h"

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

			auto RegisterArray = GetStaticTypeRegisterArray();
			Assert::AreEqual((size_t)1, RegisterArray.size());
			/*
			auto Types = Library->GetTypes();
			Assert::IsFalse(Types.size() == 0);
			auto Iter = std::find(Types.begin(), Types.end(), ObjectType);
			Assert::IsFalse(Iter == Types.end());
			Assert::AreEqual((*Iter)->GetName(), ObjectType->GetName());
			*/
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

		TEST_METHOD(PropertyValueTest)
		{
			HObject* GameObject = new HObject();

			HClass* GameType = HObject::StaticClass();

			delete GameObject;
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
