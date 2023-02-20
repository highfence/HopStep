#include "World.h"
#include "..\..\Core\CoreExport.h"
// Todo: Temp
#include "..\..\Core\Import\FbxImporter.h"

namespace HopStep
{
	bool HWorld::InitWorld()
	{
		HFbxImporter Importer;
		Importer.OpenFile(TEXT(""));

		return false;
	}
}