#include "AssetImporter.h"

#include "Core\Misc\StringUtil.h"
#include "Core\Misc\DebugUtils.h"

#include "assimp/cimport.h"
#include "assimp/postprocess.h"

namespace HopStep
{
	bool HAssetImporter::ImportFromFile(const HString& Filename)
	{
		const HAssimpScene* Scene = LoadAISceneFromFile(Filename);
		HCheck(Scene != nullptr);

		MeshDatas.resize(Scene->mNumMeshes);
		NumMaterials = Scene->mNumMaterials;

		for (Size_t MeshIndex = { 0u }; MeshIndex < MeshDatas.size(); ++MeshIndex)
		{
			const HAssimpMesh* Mesh = Scene->mMeshes[MeshIndex];

			MeshDatas[MeshIndex].Vertices.reserve(Mesh->mNumVertices);

			for (Size_t VertexIndex = { 0u }; VertexIndex < Mesh->mNumVertices; ++VertexIndex)
			{
				HVertex VertexData =
				{
					.Position = XMFLOAT3(&Mesh->mVertices[VertexIndex].x),
					// .Normal = XMFLOAT3(&Mesh->mNormals[VertexIndex].x),
					// .UV = Mesh->HasTextureCoords(0) ? XMFLOAT2(&Mesh->mTextureCoords[0][VertexIndex].x) : XMFLOAT2(0.0f, 0.0f)
				};

				MeshDatas[MeshIndex].Vertices.push_back(VertexData);
			}

			MeshDatas[MeshIndex].Indexes.reserve(Mesh->mNumFaces * 3);

			for (Size_t FaceIndex = { 0u }; FaceIndex < Mesh->mNumFaces; ++FaceIndex)
			{
				const HAssimpTriangleFace& Face = Mesh->mFaces[FaceIndex];

				MeshDatas[MeshIndex].Indexes.push_back(Face.mIndices[0]);
				MeshDatas[MeshIndex].Indexes.push_back(Face.mIndices[1]);
				MeshDatas[MeshIndex].Indexes.push_back(Face.mIndices[2]);
			}
		}

		return true;
	}

	const HAssimpScene* HAssetImporter::LoadAISceneFromFile(const HString& Filename) const
	{
		char* CharName = HStringUtil::AllocateNewCharFromHChar(Filename.c_str());

		const HAssimpScene* Scene = aiImportFile(CharName,
			aiProcess_JoinIdenticalVertices |       // ������ ������ ����, �ε��� ����ȭ
			aiProcess_ValidateDataStructure |       // �δ��� ����� ����
			aiProcess_ImproveCacheLocality |        // ��� ������ ĳ����ġ�� ����
			aiProcess_RemoveRedundantMaterials |    // �ߺ��� ���͸��� ����
			aiProcess_GenUVCoords |                 // ����, ������, ���� �� ��� ������ ������ UV�� ��ȯ
			aiProcess_TransformUVCoords |           // UV ��ȯ ó���� (�����ϸ�, ��ȯ...)
			aiProcess_FindInstances |               // �ν��Ͻ��� �Ž��� �˻��Ͽ� �ϳ��� �����Ϳ� ���� ������ ����
			aiProcess_LimitBoneWeights |            // ������ ���� ����ġ�� �ִ� 4���� ����
			aiProcess_OptimizeMeshes |              // ������ ��� ���� �Ž��� ����
			aiProcess_GenSmoothNormals |            // �ε巯�� �븻����(��������) ����
			aiProcess_SplitLargeMeshes |            // �Ŵ��� �ϳ��� �Ž��� �����Ž���� ����(����)
			aiProcess_Triangulate |                 // 3�� �̻��� �𼭸��� ���� �ٰ��� ���� �ﰢ������ ����(����)
			aiProcess_ConvertToLeftHanded |         // D3D�� �޼���ǥ��� ��ȯ
			aiProcess_SortByPType);

		delete[] CharName;
		return Scene;
	}
}