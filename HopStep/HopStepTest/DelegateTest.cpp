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
			TDelegate<void()> TestDelegate;

			TestDelegate.BindLambda();
		}
	};
}
