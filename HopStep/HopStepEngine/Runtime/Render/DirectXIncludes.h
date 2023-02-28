#pragma once

// DirectX library
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "D3DCompiler.lib")

// DirectX includes
#include <dxgi1_6.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <wrl/client.h>
#include "d3dx12.h"

// Custom
#include "..\..\Core\Windows\WindowsSystemIncludes.h"
#include "Core\Misc\GenericMemory.h"

// Namespace Aliasing
namespace HopStep
{
	// DirectX namespace aliasing
	using XMMATRIX = ::DirectX::XMMATRIX;
	using XMVECTOR = ::DirectX::XMVECTOR;
	using XMFLOAT2 = ::DirectX::XMFLOAT2;
	using XMFLOAT3 = ::DirectX::XMFLOAT3;
	using XMFLOAT4 = ::DirectX::XMFLOAT4;

	using XMFLOAT4X4 = ::DirectX::XMFLOAT4X4;

	// Microsoft namespace aliasing
	template<class TComObject>
	using ComPtr = ::Microsoft::WRL::ComPtr<TComObject>;
}

