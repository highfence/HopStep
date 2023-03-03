#pragma once
#include "CoreObject/CoreObjectExport.h"
#include "DirectXIncludes.h"

namespace HopStep
{
	struct HVertex
	{
		XMFLOAT3 Position;
		XMFLOAT4 Color;
		// XMFLOAT3 Normal;
		// XMFLOAT2 UV;
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

	// HMeshResource 하위의 범위를 정의하는 클래스.
	// 여러 메시 데이터가 하나의 VB/IB에 저장되는 경우에 해당.
	struct HSubmeshInfo
	{
		uint32 IndexCount = 0u;
		uint32 StartIndex = 0u;
		int32 BaseVertex = 0;

		HBoundingBox Bounds;
	};

	struct HMeshResource
	{
		ComPtr<ID3DBlob> VertexBufferCPU = nullptr;
		ComPtr<ID3DBlob> IndexBufferCPU = nullptr;

		ComPtr<ID3D12Resource> VertexBufferGPU = nullptr;
		ComPtr<ID3D12Resource> IndexBufferGPU = nullptr;

		ComPtr<ID3D12Resource> VertexBufferUploader = nullptr;
		ComPtr<ID3D12Resource> IndexBufferUploader = nullptr;

		uint32 VertexByteStride = 0u;
		uint32 VertexBufferByteSize = 0u;
		DXGI_FORMAT IndexFormat = DXGI_FORMAT_R16_UINT;
		uint32 IndexBufferByteSize = 0u;

		TMap<HString, HSubmeshInfo> Submeshes;

		D3D12_VERTEX_BUFFER_VIEW VertexBufferView() const 
		{
			D3D12_VERTEX_BUFFER_VIEW View = 
			{
				.BufferLocation = VertexBufferGPU->GetGPUVirtualAddress(),
				.SizeInBytes = VertexBufferByteSize,
				.StrideInBytes = VertexByteStride,
			};
			return View;
		}

		D3D12_INDEX_BUFFER_VIEW IndexBufferView() const
		{
			D3D12_INDEX_BUFFER_VIEW View =
			{
				.BufferLocation = IndexBufferGPU->GetGPUVirtualAddress(),
				.SizeInBytes = IndexBufferByteSize,
				.Format = IndexFormat
			};
			return View;
		}

		// GPU로의 업로드가 끝난 후 Uploader들을 dispose 할 수 있다.
		void DisposeUploaders()
		{
			VertexBufferUploader = nullptr;
			IndexBufferUploader = nullptr;
		}
	};
}