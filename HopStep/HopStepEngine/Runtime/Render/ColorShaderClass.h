#pragma once
#include "..\..\Core\CoreExport.h"
#include "DirectXIncludes.h"

namespace HopStep
{
	class HColorShaderClass
	{
	public:

		struct HMatrixBufferType
		{
			XMMATRIX World;
			XMMATRIX View;
			XMMATRIX Projection;
		};

		HColorShaderClass();
		virtual ~HColorShaderClass();

		bool Initialize(ID3D11Device*, HWND);
		void Shutdown();
		bool Render(ID3D11DeviceContext*, int32, XMMATRIX, XMMATRIX, XMMATRIX);

	protected:

		bool InitializeShader(ID3D11Device*, HWND, const HChar*, const HChar*);
		void ShutdownShader();
		void OutputShaderErrorMessage(ID3DBlob*, HWND, const HChar*);

		bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX);
		void RenderShader(ID3D11DeviceContext*, int32);

		ID3D11VertexShader* VertexShader;
		ID3D11PixelShader* PixelShader;
		ID3D11InputLayout* Layout;
		ID3D11Buffer* MatrixBuffer;
	};
}