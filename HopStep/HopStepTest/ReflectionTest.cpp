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

			auto& Library = HMetadataLibrary::Get();

			auto Types = Library.GetTypes();
			Assert::AreEqual(Types.size(), std::size_t{ 0 });
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

			delete GameObject;
		}
	};
}
