#pragma once
#include "DirectXIncludes.h"

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

			// ConstantBuffer�� ��쿡�� 256�� ����� Size�� ��������� �Ѵ�.
			if (bIsConstantBuffer)
			{
				ElementByteSize = (ElementCount + 255) & ~255;
			}

			ThrowIfFailed(Device->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Buffer(ElementCount * ElementByteSize),
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

		void CopyData(int32 ElementIndex, const TResourceType& InData)
		{
			HGenericMemory::MemCpy(&MappedData[ElementIndex * ElementByteSize, &InData, sizeof(TResourceType)]);
		}

	private:

		ComPtr<ID3D12Resource> UploadBuffer;
		HByte* MappedData;

		uint32 ElementByteSize = 0u;
		bool bIsConstantBuffer = false;
	};
}