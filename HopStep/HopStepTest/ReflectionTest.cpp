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
	};
}
