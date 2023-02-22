#include "World.h"
#include "..\..\Core\CoreExport.h"
// Todo: Temp
#include "Runtime/Engine/AssetImporter.h"

namespace HopStep
{
	bool HWorld::InitWorld()
	{
		HString AssetPath = HPaths::ContentPath().append(TEXT("tree.fbx"));

		HAssetImporter Importer;
		Importer.ImportFromFile(AssetPath);

		return false;
	}
}