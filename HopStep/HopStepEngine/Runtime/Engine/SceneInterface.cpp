#include "SceneInterface.h"
#include "Runtime/Engine/Scene.h"

namespace HopStep
{
	HSceneInterface* HSceneInterface::CreateScene()
	{
		return new HScene();
	}

	HSceneInterface::HSceneInterface()
	{
	}

	HSceneInterface::~HSceneInterface()
	{
	}
}