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

				HopStep::Internal::DetectTrailingDigitFromString(NoDigitString, MustBeNoDigit, MustBeNoLength);

				Assert::AreEqual((uint32)0, MustBeNoDigit);
				Assert::AreEqual((uint32)0, MustBeNoLength);
			}

			// One digit string test
			{
				HopStep::HString OneDigitString(TEXT("OnDigitString9"));
				uint32 Digit = 0;
				uint32 Length = 0;

				HopStep::Internal::DetectTrailingDigitFromString(OneDigitString, Digit, Length);

				Assert::AreEqual((uint32)9, Digit);
				Assert::AreEqual((uint32)1, Length);
			}

			// Multiple digit string test
			{
				HopStep::HString MultipleDigitString(TEXT("MultipleDigitString49783"));
				uint32 Digit = 0;
				uint32 Length = 0;

				HopStep::Internal::DetectTrailingDigitFromString(MultipleDigitString, Digit, Length);

				Assert::AreEqual((uint32)49783, Digit);
				Assert::AreEqual((uint32)5, Length);
			}

			// Minus digit string test
			{
				HopStep::HString MinusDigitString(TEXT("MinusDigitString-883"));
				uint32 Digit = 0;
				uint32 Length = 0;

				HopStep::Internal::DetectTrailingDigitFromString(MinusDigitString, Digit, Length);

				Assert::AreEqual((uint32)883, Digit);
				Assert::AreEqual((uint32)3, Length);
			}

			// Digit inside string test
			{
				HopStep::HString DigitInsideString(TEXT("Digit11299Inside97463String27649473"));
				uint32 Digit = 0;
				uint32 Length = 0;

				HopStep::Internal::DetectTrailingDigitFromString(DigitInsideString, Digit, Length);

				Assert::AreEqual((uint32)27649473, Digit);
				Assert::AreEqual((uint32)8, Length);
			}
		}
	};
}
