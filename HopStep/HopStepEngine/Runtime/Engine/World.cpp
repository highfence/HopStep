#include "World.h"
#include "..\..\Core\CoreExport.h"
// Todo: Temp
#include "..\..\Core\Import\AssetImporter.h"

namespace HopStep
{
	bool HWorld::InitWorld()
	{
		HString AssetPath = HPaths::ContentPath().append(TEXT("Lowpoly_tree_sample.fbx"));

		HAssetImporter Importer;
		Importer.OpenFile(AssetPath);

		return false;
	}
}