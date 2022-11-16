#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HopStepTest
{
	using HCommandLine = HopStep::HCommandLine;

	TEST_CLASS(HCommandLineTest)
	{
	public:

		TEST_METHOD(HCommandLineSet)
		{
			const HopStep::HChar* TestString = TEXT("Is this a command?");

			HCommandLine::Set(TestString);

			Assert::IsTrue(HCommandLine::IsInit());

			const HopStep::HChar* SetString = HCommandLine::Get();

			Assert::AreEqual(SetString, TestString);
		}
	};
}

