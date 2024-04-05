#include "World.h"
#include "Runtime/Engine/SceneInterface.h"
#include "Level.h"

namespace HopStep
{
	HWorld::~HWorld()
	{
	}

	bool HWorld::InitWorld()
	{
		/*
		HString AssetPath = HPaths::ContentPath().append(TEXT("tree.fbx"));

		HAssetImporter Importer;
		Importer.ImportFromFile(AssetPath);
		*/



		return false;
	}

	void HWorld::Tick(float deltaTime)
	{

	}
}