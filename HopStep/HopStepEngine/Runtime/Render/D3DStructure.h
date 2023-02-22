#pragma once
#include "DirectXIncludes.h"

namespace HopStep
{
	struct HVertex
	{
		XMFLOAT3 Position;
		XMFLOAT3 Normal;
		XMFLOAT2 UV;
	};

	struct HMeshData
	{
		TArray<HVertex> Vertices;
		TArray<uint32> Indexes;
		uint32 MaterialIndex = 0u;
	};
}