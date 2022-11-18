#pragma once

// DirectX library
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

// DirectX includes
#include <dxgi.h>
#include <d3d11.h>
#include <d3dcommon.h>
#include <DirectXMath.h>

// Custom
#include "..\..\Core\Windows\WindowsSystemIncludes.h"

// Namespace
namespace HopStep
{
	using XMMATRIX = ::DirectX::XMMATRIX;
}
