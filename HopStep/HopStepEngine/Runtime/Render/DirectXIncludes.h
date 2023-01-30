#pragma once

// DirectX library
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "D3DCompiler.lib")

// DirectX includes
#include <dxgi.h>
#include <d3d12.h>
#include <d3dcommon.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>
#include <wrl.h>
#include <wrl/client.h>

// Custom
#include "..\..\Core\Windows\WindowsSystemIncludes.h"

// Namespace Aliasing
namespace HopStep
{
	// DirectX namespace aliasing
	using XMMATRIX = ::DirectX::XMMATRIX;
	using XMVECTOR = ::DirectX::XMVECTOR;
	using XMFLOAT3 = ::DirectX::XMFLOAT3;
	using XMFLOAT4 = ::DirectX::XMFLOAT4;

	// Microsoft namespace aliasing
	template<class TComObject>
	using ComPtr = ::Microsoft::WRL::ComPtr<TComObject>;
}

