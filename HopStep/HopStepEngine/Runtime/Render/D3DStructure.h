#pragma once
#include "CoreObject/CoreObjectExport.h"
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
		// HName Name;

		TArray<HVertex> Vertices;
		TArray<uint32> Indexes;
		uint32 MaterialIndex = 0u;
	};

	struct HObjectConstantBuffer
	{
		XMFLOAT4X4 WorldViewProj = XMFLOAT4X4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	};
}