#include "pch.h"
#include "CppUnitTest.h"
#include "..\HopStepEngine\Core\Misc\EngineConfig.h"
#include "..\HopStepEngine\Core\Delegates\DelegateSigniture.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace HopStep::Core::Delegates;

namespace HopStepTest
{
	int32 gA = 0;
	void StaticMethodTestFunc() { ++gA;	};

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
			DelegateBase.Unbind();

			TDelegate<int32(int32, int32)> DelegateBaseWithReturn;
			DelegateBaseWithReturn.BindLambda([](int32 A, int32 B) -> int32 { return A * B; });
			Assert::AreEqual((int32)32, DelegateBaseWithReturn.Execute(4, 8));
			DelegateBaseWithReturn.Unbind();
		}

		TEST_METHOD(DelegateStaticMethod)
		{
			TDelegate<void()> StaticMethodEvent;
			StaticMethodEvent.BindStatic(&StaticMethodTestFunc);

			Assert::IsTrue(StaticMethodEvent.ExecuteIfBound());
			Assert::AreEqual((int32)1, gA);
			StaticMethodEvent.Unbind();
		}

		TEST_METHOD(DelegateClassMethod)
		{
			class DelegateClassMethodTest
			{
			public:
				int32 A = 0;
				int32 B = 0;

				void MakeAIncrease() { ++A; }
				void MakeBDecreaseBy(int32 Value) { B -= Value; }

				int32 GetAMultiplyB() const { return A * B; }
			};

			DelegateClassMethodTest Object;
			Assert::AreEqual((int32)0, Object.A);

			TDelegate<void()> DelegateA;
			DelegateA.BindMethod(&Object, &DelegateClassMethodTest::MakeAIncrease);
			DelegateA.ExecuteIfBound();
			DelegateA.Unbind();

			Assert::AreEqual((int32)1, Object.A);

			TDelegate<void(int32)> DelegateB;
			DelegateB.BindMethod(&Object, &DelegateClassMethodTest::MakeBDecreaseBy);
			DelegateB.ExecuteIfBound(7);
			DelegateB.Unbind();

			Assert::AreEqual((int32)-7, Object.B);

			TDelegate<int32()> DelegateC;
			DelegateC.BindMethod(&Object, &DelegateClassMethodTest::GetAMultiplyB);
			int32 Result = DelegateC.Execute();
			Assert::AreEqual((int32)-7, Result);
			DelegateC.Unbind();
		}
	};
}
