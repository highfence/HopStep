#pragma once
#include "Core\HopStepOverrides.h"
#include "Runtime\Render\D3DStructure.h"
#include "assimp/scene.h"

#if _DEBUG
#pragma comment(lib, "assimp-vc143-mtd.lib")
#endif

// Namespace Aliasing
namespace HopStep
{
	using HAssimpScene = ::aiScene;
	using HAssimpMesh = ::aiMesh;
	using HAssimpTriangleFace = ::aiFace;
}

namespace HopStep 
{
	class HAssetImporter
	{
	public:

		bool ImportFromFile(const HString& Filename);

		TArray<HMeshData>& GetMeshData() { return MeshDatas; }

	private:

		const HAssimpScene* LoadAISceneFromFile(const HString& Filename) const;

		TArray<HMeshData> MeshDatas;

		uint32 NumVertices = 0u;
		uint32 NumMaterials = 0u;
	};
}