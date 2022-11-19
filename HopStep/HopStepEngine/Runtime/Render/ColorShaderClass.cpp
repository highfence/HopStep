#include "..\..\Core\CoreExport.h"
#include "ColorShaderClass.h"
#include <fstream>

namespace HopStep
{
	HColorShaderClass::HColorShaderClass()
		: VertexShader(nullptr)
		, PixelShader(nullptr)
		, Layout(nullptr)
		, MatrixBuffer(nullptr)
	{
	}

	HColorShaderClass::~HColorShaderClass()
	{
		Shutdown();
	}

	bool HColorShaderClass::Initialize(ID3D11Device* Device, HWND WindowHandle)
	{
		return InitializeShader(
			Device,
			WindowHandle,
			HPaths::ShaderPath().append(TEXT("\\Color.vs")).c_str(),
			HPaths::ShaderPath().append(TEXT("\\Color.ps")).c_str());
	}

	void HColorShaderClass::Shutdown()
	{
		ShutdownShader();
	}

	bool HColorShaderClass::Render(ID3D11DeviceContext* DeviceContext, int32 IndexCount, XMMATRIX World, XMMATRIX View, XMMATRIX Projection)
	{
		bool Result = SetShaderParameters(DeviceContext, World, View, Projection);
		if (Result == false)
		{
			return false;
		}

		RenderShader(DeviceContext, IndexCount);
		return true;
	}

	bool HColorShaderClass::InitializeShader(ID3D11Device* Device, HWND WindowHandle, const HChar* VSFilename, const HChar* PSFilename)
	{
		ID3DBlob* VertexShaderBuffer = nullptr;
		ID3DBlob* ErrorMeesage = nullptr;

		HRESULT Result = D3DCompileFromFile(
			VSFilename,
			NULL,
			NULL,
			"ColorVertexShader",
			"vs_5_0",
			D3D10_SHADER_ENABLE_STRICTNESS,
			NULL,
			&VertexShaderBuffer,
			&ErrorMeesage);

		if (FAILED(Result))
		{
			if (ErrorMeesage != nullptr)
			{
				OutputShaderErrorMessage(ErrorMeesage, WindowHandle, VSFilename);
			}
			else
			{
				MessageBox(WindowHandle, VSFilename, TEXT("Missing Shader File"), MB_OK);
			}
			return false;
		}

		ID3DBlob* PixelShaderBuffer = nullptr;
		Result = D3DCompileFromFile(
			PSFilename,
			NULL,
			NULL,
			"ColorPixelShader",
			"ps_5_0",
			D3D10_SHADER_ENABLE_STRICTNESS,
			NULL,
			&PixelShaderBuffer,
			&ErrorMeesage);

		if (FAILED(Result))
		{
			if (ErrorMeesage != nullptr)
			{
				OutputShaderErrorMessage(ErrorMeesage, WindowHandle, PSFilename);
			}
			else
			{
				MessageBox(WindowHandle, PSFilename, TEXT("Missing Shader File"), MB_OK);
			}
			return false;
		}

		Result = Device->CreateVertexShader(VertexShaderBuffer->GetBufferPointer(), VertexShaderBuffer->GetBufferSize(), NULL, &VertexShader);
		if (FAILED(Result)) return false;

		Result = Device->CreatePixelShader(PixelShaderBuffer->GetBufferPointer(), PixelShaderBuffer->GetBufferSize(), NULL, &PixelShader);
		if (FAILED(Result)) return false;

		D3D11_INPUT_ELEMENT_DESC PolygonLayout[2];
		{
			PolygonLayout[0].SemanticName = "POSITION";
			PolygonLayout[0].SemanticIndex = 0;
			PolygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
			PolygonLayout[0].InputSlot = 0;
			PolygonLayout[0].AlignedByteOffset = 0;
			PolygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			PolygonLayout[0].InstanceDataStepRate = 0;

			PolygonLayout[1].SemanticName = "COLOR";
			PolygonLayout[1].SemanticIndex = 0;
			PolygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			PolygonLayout[1].InputSlot = 0;
			PolygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			PolygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			PolygonLayout[1].InstanceDataStepRate = 0;
		}

		int32 NumElements = sizeof(PolygonLayout) / sizeof(PolygonLayout[0]);
		Result = Device->CreateInputLayout(PolygonLayout, NumElements, VertexShaderBuffer->GetBufferPointer(), VertexShaderBuffer->GetBufferSize(), &Layout);
		if (FAILED(Result)) return false;

		SAFE_RELEASE(VertexShaderBuffer);
		SAFE_RELEASE(PixelShaderBuffer);

		D3D11_BUFFER_DESC MatrixBufferDesc =
		{
			.ByteWidth = sizeof(HMatrixBufferType),
			.Usage = D3D11_USAGE_DYNAMIC,
			.BindFlags = D3D11_BIND_CONSTANT_BUFFER,
			.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE,
			.MiscFlags = 0,
			.StructureByteStride = 0
		};

		Result = Device->CreateBuffer(&MatrixBufferDesc, NULL, &MatrixBuffer);
		if (FAILED(Result)) return false;

		return true;
	}

	void HColorShaderClass::ShutdownShader()
	{
		SAFE_RELEASE(MatrixBuffer);
		SAFE_RELEASE(Layout);
		SAFE_RELEASE(PixelShader);
		SAFE_RELEASE(VertexShader);
	}

	void HColorShaderClass::OutputShaderErrorMessage(ID3DBlob* ErrorMessage, HWND WindowHandle, const HChar* ShaderFilename)
	{
		char* ComplieError = (char*)(ErrorMessage->GetBufferPointer());
		HSize BufferSize = ErrorMessage->GetBufferSize();

		std::ofstream FileStream;
		{
			FileStream.open("ShaderError.log");

			for (HSize Idx = 0; Idx < BufferSize; ++Idx)
			{
				FileStream << ComplieError[Idx];
			}

			FileStream.close();
		}

		SAFE_RELEASE(ErrorMessage);
		MessageBox(WindowHandle, TEXT("Error compling shader. Check ShaderError.log for message."), ShaderFilename, MB_OK);
		return;
	}

	bool HColorShaderClass::SetShaderParameters(ID3D11DeviceContext* DeviceContext, XMMATRIX World, XMMATRIX View, XMMATRIX Projection)
	{
		World = DirectX::XMMatrixTranspose(World);
		View = DirectX::XMMatrixTranspose(View);
		Projection = DirectX::XMMatrixTranspose(Projection);

		D3D11_MAPPED_SUBRESOURCE MappedResource;
		HRESULT Result = DeviceContext->Map(MatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
		if (FAILED(Result)) return false;

		HMatrixBufferType* Data = (HMatrixBufferType*)MappedResource.pData;
		{
			Data->World = World;
			Data->View = View;
			Data->Projection = Projection;
		}

		DeviceContext->Unmap(MatrixBuffer, 0);
		UINT BufferNumber = 0;
		DeviceContext->VSSetConstantBuffers(BufferNumber, 1, &MatrixBuffer);
		return true;
	}

	void HColorShaderClass::RenderShader(ID3D11DeviceContext* DeviceContext, int32 IndexCount)
	{
		DeviceContext->IASetInputLayout(Layout);
		DeviceContext->VSSetShader(VertexShader, NULL, 0);
		DeviceContext->PSSetShader(PixelShader, NULL, 0);
		DeviceContext->DrawIndexed(IndexCount, 0, 0);
	}
}