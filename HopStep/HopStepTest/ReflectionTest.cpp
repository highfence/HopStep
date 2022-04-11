#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HopStepTest
{
	TEST_CLASS(ReflectionTest)
	{
	public:
		TEST_METHOD(MetadataLibraryAccessTest)
		{
			std::cout << "MetadataLibraryAccessTest started" << std::endl;

			auto* Library = HMetadataLibrary::Get();
			Assert::IsNotNull(Library);

			HType* ObjectType = HObject::StaticClass();
			auto Types = Library->GetTypes();
			Assert::IsFalse(Types.size() == 0);
			auto Iter = std::find(Types.begin(), Types.end(), ObjectType);
			Assert::IsFalse(Iter == Types.end());
			Assert::AreEqual((*Iter)->GetName(), ObjectType->GetName());
		}

		TEST_METHOD(GameTypeAccessTest)
		{
			HType* GameType = HObject::StaticClass();
			Assert::IsNotNull(GameType);
		}

		TEST_METHOD(GameTypeNameTest)
		{
			HObject* GameObject = new HObject();

			HType* GameType = HObject::StaticClass();
			Assert::AreEqual(GameObject->FriendlyName, std::wstring_view(GameType->GetName()));
			Assert::AreEqual(GameObject->FriendlyName, std::wstring_view(L"HObject"));

			delete GameObject;
		}
	};
}
