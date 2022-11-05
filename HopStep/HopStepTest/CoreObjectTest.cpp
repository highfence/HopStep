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
			{
				HopStep::HString NoDigitString(TEXT("NoDigitString"));
				uint32 MustBeNoDigit = 0;
				uint32 MustBeNoLength = 0;

				HopStep::Internal::DetectTrailingDigitFromString(NoDigitString, MustBeNoDigit, MustBeNoLength);

				Assert::AreEqual((uint32)0, MustBeNoDigit);
				Assert::AreEqual((uint32)0, MustBeNoLength);
			}
		}
	};
}
