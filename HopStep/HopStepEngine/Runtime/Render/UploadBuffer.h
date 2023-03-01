#pragma once
#include "DirectXIncludes.h"
#include "D3DUtils.h"

namespace HopStep
{
	template <typename TResourceType>
	class TUploadBuffer
	{
	public:

		TUploadBuffer(ID3D12Device* Device, uint32 ElementCount, bool bIsConstant)
			: bIsConstantBuffer(bIsConstant)
		{
			ElementByteSize = sizeof(TResourceType);

			// ConstantBuffer의 경우에는 256의 배수로 Size를 세팅해줘야 한다.
			if (bIsConstantBuffer)
			{
				ElementByteSize = (ElementCount + 255) & ~255;
			}

			auto Property = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
			auto Buffer = CD3DX12_RESOURCE_DESC::Buffer(ElementCount * ElementByteSize);

			ThrowIfFailed(Device->CreateCommittedResource(
				&Property,
				D3D12_HEAP_FLAG_NONE,
				&Buffer,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&UploadBuffer)
			));

			ThrowIfFailed(UploadBuffer->Map(0, nullptr, reinterpret_cast<void**>(&MappedData)));
		}

		TUploadBuffer(const TUploadBuffer& rhs) = delete;
		TUploadBuffer& operator=(const TUploadBuffer& rhs) = delete;

		~TUploadBuffer()
		{
			if (UploadBuffer != nullptr)
			{
				UploadBuffer->Unmap(0, nullptr);
			}

			MappedData = nullptr;
		}

		ID3D12Resource* Resource() const { return UploadBuffer.Get(); }

		void CopyData(int32 ElementIndex, TResourceType* InData)
		{
			HGenericMemory::MemCpy(&MappedData[ElementIndex * ElementByteSize], reinterpret_cast<void*>(InData), sizeof(TResourceType));
		}

		uint32 GetElementByteSize() const { return ElementByteSize; }

	private:

		ComPtr<ID3D12Resource> UploadBuffer;
		HByte* MappedData;

		uint32 ElementByteSize = 0u;
		bool bIsConstantBuffer = false;
	};
}