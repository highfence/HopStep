#include "AssetImporter.h"
#include "..\Misc\StringUtil.h"
#include "..\Misc\DebugUtils.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"

namespace HopStep
{
	bool HAssetImporter::OpenFile(const HString& Filename)
	{
		auto Scene = LoadAISceneFromFile(Filename);
		HCheck(Scene != nullptr);




		return false;
	}

	const aiScene* HAssetImporter::LoadAISceneFromFile(const HString& Filename) const
	{
		char* CharName = HStringUtil::AllocateNewCharFromHChar(Filename.c_str());

		const ::aiScene* Scene = aiImportFile(CharName,
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
		return reinterpret_cast<const aiScene*>(Scene);
	}
}