#include "pch.h"
#include "CppUnitTest.h"
#include "..\HopStepEngine\Core\Misc\EngineConfig.h"
#include "..\HopStepEngine\Core\Delegates\DelegateSigniture.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace HopStep::Core::Delegates;

namespace HopStepTest
{
	TEST_CLASS(DelegateTest)
	{
	public:
		
		TEST_METHOD(DelegateLambdaBound)
		{
			int32 Ref = 0;

			auto Lambda = [&Ref](int32 A, int32 B) -> void
			{
				Ref = A + B;
			};

			TDelegate<void(int32, int32)> DelegateBase;
			Assert::IsFalse(DelegateBase.ExecuteIfBound(0, 0));

			DelegateBase.BindLambda(Lambda);
			Assert::IsTrue(DelegateBase.ExecuteIfBound(3, 5));

			Assert::AreEqual((int32)8, Ref);
		}
	};
}
