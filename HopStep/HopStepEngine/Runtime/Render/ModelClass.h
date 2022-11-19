#pragma once
#include "..\..\Core\CoreExport.h"
#include "DirectXIncludes.h"

namespace HopStep
{
	// Todo: Need refactoring
	class HModelClass
	{
	public:

		// Must fit with ColorShaderClass
		struct HVertexType
		{
			XMFLOAT3 Position;
			XMFLOAT4 Color;
		};

		HModelClass();
		HModelClass(const HModelClass&);
		virtual ~HModelClass();

		bool Initialize(ID3D11Device*);
		void Shutdown();
		void Render(ID3D11DeviceContext*);

		uint32 GetIndexCount();

	protected:

		bool InitializeBuffers(ID3D11Device*);
		void ReleaseBuffers();
		void RenderBuffers(ID3D11DeviceContext*);

		ID3D11Buffer* VertexBuffer;
		uint32 VertexCount;

		ID3D11Buffer* IndexBuffer;
		uint32 IndexCount;
	};
}