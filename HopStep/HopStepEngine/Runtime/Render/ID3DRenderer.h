#pragma once

namespace HopStep
{
	class ID3DRenderer
	{
	public:

		virtual ~ID3DRenderer() {}

		static ID3DRenderer* CreateD3DRenderer();
		
		virtual bool InitDirect3D() = 0;
	};
}