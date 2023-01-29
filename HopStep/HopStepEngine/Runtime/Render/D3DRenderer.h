#pragma once
#include "DirectXIncludes.h"
#include "ID3DRenderer.h"

namespace HopStep
{
	class HD3DRenderer : public ID3DRenderer
	{
	public:

		virtual ~HD3DRenderer();

		virtual bool InitDirect3D() override;

	private:

		Microsoft::WRL::ComPtr<ID3D12Device> D3DDevice;
	};
}