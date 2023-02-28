#pragma once
#include "DirectXIncludes.h"
#include "D3DStructure.h"

namespace HopStep
{

	//
	class HFrameResource
	{
	public:

		HFrameResource(ID3D12Device* Device, uint32 PassCount, uint32 ObjectCount, uint32 MaterialCount);
		HFrameResource(const HFrameResource& rhs) = delete;
		HFrameResource& operator=(const HFrameResource& rhs) = delete;

		~HFrameResource();

		ComPtr<ID3D12CommandAllocator> CommandAllocator;

	};
}