#include "pch.h"
#include "CppUnitTest.h"
#include "..\HopStepEngine\HopStep.h"
#include "..\HopStepEngine\CoreObject\Object\NameTypes.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HopStepTest
{
	TEST_CLASS(CoreObjectTest)
	{
	public:
		
		TEST_METHOD(HName_DetectTrailingDigitFromStringTest)
		{
			// No digit string test
			{
				HopStep::HString NoDigitString(TEXT("NoDigitString"));
				uint32 MustBeNoDigit = 0;
				uint32 MustBeNoLength = 0;

				HopStep::Internal::HNameHelper::DetectTrailingDigitFromString(NoDigitString, MustBeNoDigit, MustBeNoLength);

				Assert::AreEqual((uint32)0, MustBeNoDigit);
				Assert::AreEqual((uint32)0, MustBeNoLength);
			}

			// One digit string test
			{
				HopStep::HString OneDigitString(TEXT("OnDigitString9"));
				uint32 Digit = 0;
				uint32 Length = 0;

				HopStep::Internal::HNameHelper::DetectTrailingDigitFromString(OneDigitString, Digit, Length);

				Assert::AreEqual((uint32)9, Digit);
				Assert::AreEqual((uint32)1, Length);
			}

			// Multiple digit string test
			{
				HopStep::HString MultipleDigitString(TEXT("MultipleDigitString49783"));
				uint32 Digit = 0;
				uint32 Length = 0;

				HopStep::Internal::HNameHelper::DetectTrailingDigitFromString(MultipleDigitString, Digit, Length);

				Assert::AreEqual((uint32)49783, Digit);
				Assert::AreEqual((uint32)5, Length);
			}

			// Minus digit string test
			{
				HopStep::HString MinusDigitString(TEXT("MinusDigitString-883"));
				uint32 Digit = 0;
				uint32 Length = 0;

				HopStep::Internal::HNameHelper::DetectTrailingDigitFromString(MinusDigitString, Digit, Length);

				Assert::AreEqual((uint32)883, Digit);
				Assert::AreEqual((uint32)3, Length);
			}

			// Digit inside string test
			{
				HopStep::HString DigitInsideString(TEXT("Digit11299Inside97463String27649473"));
				uint32 Digit = 0;
				uint32 Length = 0;

				HopStep::Internal::HNameHelper::DetectTrailingDigitFromString(DigitInsideString, Digit, Length);

				Assert::AreEqual((uint32)27649473, Digit);
				Assert::AreEqual((uint32)8, Length);
			}

			// Only number string test
			{
				HopStep::HString OnlyNumberString(TEXT("1234782345"));
				uint32 Digit = 0;
				uint32 Length = 0;

				HopStep::Internal::HNameHelper::DetectTrailingDigitFromString(OnlyNumberString, Digit, Length);

				Assert::AreEqual((uint32)1234782345, Digit);
				Assert::AreEqual((uint32)10, Length);
			}
		}

		TEST_METHOD(HName_Test_IsValid)
		{
			HopStep::HName ValidName(TEXT("ValidName"));
			Assert::IsTrue(ValidName.IsValid());

			HopStep::HName InValidName;
			Assert::IsFalse(InValidName.IsValid());
		}

		TEST_METHOD(HName_Test_ToString)
		{
			HopStep::HString TestString(TEXT("TestString"));
			HopStep::HName TestName = HopStep::HName(TestString);

			Assert::AreEqual(TestString, TestName.ToString());

			HopStep::HString AnotherTestString(TEXT("AnotherTestString"));
			HopStep::HName AnotherTestName = HopStep::HName(AnotherTestString);

			Assert::AreEqual(AnotherTestString, AnotherTestName.ToString());
		}
	};
}
