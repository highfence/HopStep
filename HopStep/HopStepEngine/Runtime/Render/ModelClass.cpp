#include "ModelClass.h"

namespace HopStep
{
	HModelClass::HModelClass()
		: VertexBuffer(nullptr)
		, IndexBuffer(nullptr)
		, VertexCount(0)
		, IndexCount(0)
	{
	}

	HModelClass::HModelClass(const HModelClass& Other)
		: VertexBuffer(Other.VertexBuffer)
		, IndexBuffer(Other.IndexBuffer)
		, VertexCount(Other.VertexCount)
		, IndexCount(Other.IndexCount)
	{
	}

	HModelClass::~HModelClass()
	{
	}

	bool HModelClass::Initialize(ID3D11Device* InDevice)
	{
		return InitializeBuffers(InDevice);
	}

	void HModelClass::Shutdown()
	{
		ReleaseBuffers();
	}

	void HModelClass::Render(ID3D11DeviceContext* InDeviceContext)
	{
		RenderBuffers(InDeviceContext);
	}

	uint32 HModelClass::GetIndexCount()
	{
		return IndexCount;
	}

	bool HModelClass::InitializeBuffers(ID3D11Device* InDevice)
	{
		// Todo: Temporary codes.
		HVertexType* Vertices = nullptr;
		{
			VertexCount = 3;
			Vertices = new HVertexType[VertexCount];
			Vertices[0].Position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
			Vertices[0].Color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

			Vertices[1].Position = XMFLOAT3(0.0f, 1.0f, 0.0f);
			Vertices[1].Color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

			Vertices[2].Position = XMFLOAT3(1.0f, -1.0f, 0.0f);
			Vertices[2].Color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
		}

		D3D11_BUFFER_DESC VertexBufferDesc =
		{
			.ByteWidth = (sizeof(HVertexType) * VertexCount),
			.Usage = D3D11_USAGE_DEFAULT,
			.BindFlags = D3D11_BIND_VERTEX_BUFFER,
			.CPUAccessFlags = 0,
			.MiscFlags = 0,
			.StructureByteStride = 0
		};

		D3D11_SUBRESOURCE_DATA VertexData =
		{
			.pSysMem = Vertices,
			.SysMemPitch = 0,
			.SysMemSlicePitch = 0
		};

		HRESULT Result = InDevice->CreateBuffer(&VertexBufferDesc, &VertexData, &VertexBuffer);
		if (FAILED(Result))
		{
			delete[] Vertices;
			return false;
		}

		uint32* Indices = nullptr;
		{
			IndexCount = 3;
			Indices = new uint32[IndexCount];

			Indices[0] = 0;
			Indices[1] = 1;
			Indices[2] = 2;
		}

		D3D11_BUFFER_DESC IndexBufferDesc =
		{
			.ByteWidth = sizeof(uint32) * IndexCount,
			.Usage = D3D11_USAGE_DEFAULT,
			.BindFlags = D3D11_BIND_INDEX_BUFFER,
			.CPUAccessFlags = 0,
			.MiscFlags = 0,
			.StructureByteStride = 0
		};

		D3D11_SUBRESOURCE_DATA IndexData =
		{
			.pSysMem = Indices,
		    .SysMemPitch = 0,
		    .SysMemSlicePitch = 0
		};

		Result = InDevice->CreateBuffer(&IndexBufferDesc, &IndexData, &IndexBuffer);

		delete[] Vertices;
		delete[] Indices;
		Vertices = nullptr;
		Indices = nullptr;

		if (FAILED(Result))
		{
			return false;
		}
		return true;
	}

	void HModelClass::ReleaseBuffers()
	{
		SAFE_RELEASE(IndexBuffer);
		SAFE_RELEASE(VertexBuffer);
	}

	void HModelClass::RenderBuffers(ID3D11DeviceContext* InDeviceContext)
	{
		UINT Stride = sizeof(HVertexType);
		UINT Offset = 0;

		InDeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &Stride, &Offset);
		InDeviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		InDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}