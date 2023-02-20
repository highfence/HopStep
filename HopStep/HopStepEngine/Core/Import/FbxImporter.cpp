#include "FbxImporter.h"
#include "ThirdParty/Assimp/include/assimp/cimport.h"

namespace HopStep
{
	bool HFbxImporter::OpenFile(const HString& Filename)
	{
		auto _ = aiImportFile("", 0);
		return false;
	}
}