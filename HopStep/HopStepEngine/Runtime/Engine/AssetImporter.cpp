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
			aiProcess_JoinIdenticalVertices |       // 동일한 꼭지점 결합, 인덱싱 최적화
			aiProcess_ValidateDataStructure |       // 로더의 출력을 검증
			aiProcess_ImproveCacheLocality |        // 출력 정점의 캐쉬위치를 개선
			aiProcess_RemoveRedundantMaterials |    // 중복된 매터리얼 제거
			aiProcess_GenUVCoords |                 // 구형, 원통형, 상자 및 평면 매핑을 적절한 UV로 변환
			aiProcess_TransformUVCoords |           // UV 변환 처리기 (스케일링, 변환...)
			aiProcess_FindInstances |               // 인스턴스된 매쉬를 검색하여 하나의 마스터에 대한 참조로 제거
			aiProcess_LimitBoneWeights |            // 정점당 뼈의 가중치를 최대 4개로 제한
			aiProcess_OptimizeMeshes |              // 가능한 경우 작은 매쉬를 조인
			aiProcess_GenSmoothNormals |            // 부드러운 노말벡터(법선벡터) 생성
			aiProcess_SplitLargeMeshes |            // 거대한 하나의 매쉬를 하위매쉬들로 분할(나눔)
			aiProcess_Triangulate |                 // 3개 이상의 모서리를 가진 다각형 면을 삼각형으로 만듬(나눔)
			aiProcess_ConvertToLeftHanded |         // D3D의 왼손좌표계로 변환
			aiProcess_SortByPType);

		delete[] CharName;
		return Scene;
	}
}