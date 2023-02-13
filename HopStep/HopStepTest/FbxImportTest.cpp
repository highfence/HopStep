#include "pch.h"
#include "CppUnitTest.h"
#include "..\HopStepEngine\Core\Import\FbxImporter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HopStepTest
{
	TEST_CLASS(FbxImportTest)
	{
	public:

		TEST_METHOD(FbxImporter_Initialize)
		{
			::HopStep::HFbxImporter Importer;
			Assert::IsTrue(Importer.Initialize());
		}

	};
}
