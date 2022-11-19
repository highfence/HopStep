#pragma once

// DirectX library
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

// DirectX includes
#include <dxgi.h>
#include <d3d11.h>
#include <d3dcommon.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

// Custom
#include "..\..\Core\Windows\WindowsSystemIncludes.h"

// Namespace Aliasing
namespace HopStep
{
	using XMMATRIX = ::DirectX::XMMATRIX;
	using XMVECTOR = ::DirectX::XMVECTOR;
	using XMFLOAT3 = ::DirectX::XMFLOAT3;
	using XMFLOAT4 = ::DirectX::XMFLOAT4;
}
