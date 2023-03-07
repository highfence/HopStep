#include "D3DUtils.h"
// for _com_error
#include <comdef.h>

namespace HopStep
{
	HDirectXException::HDirectXException(HRESULT HR, const HString& FunctionName, const HString& FileName, int32 LineNumber)
		: ErrorCode(HR)
		, FunctionName(FunctionName)
		, FileName(FileName)
		, LineNumber(LineNumber)
	{

	}
	HString HDirectXException::ToString() const
	{
		_com_error Err(ErrorCode);
		HString Msg = Err.ErrorMessage();

		return FunctionName + TEXT(" failed in ") + FileName + std::to_wstring(LineNumber) + TEXT("; Error: ") + Msg;
	}

	void _Use_decl_annotations_ HRenderPipelineUtils::GetHardwareAdapter(IDXGIFactory1* FactoryPtr, IDXGIAdapter1** OutAdaptorPtr, bool bRequestHighPerformanceAdapter)
	{
		*OutAdaptorPtr = nullptr;

		ComPtr<IDXGIAdapter1> Adaptor;
		// Todo: Why they use factory6 here?
		ComPtr<IDXGIFactory6> Factory6;

		if (SUCCEEDED(FactoryPtr->QueryInterface(IID_PPV_ARGS(&Factory6))))
		{
			DXGI_GPU_PREFERENCE GpuPreference = bRequestHighPerformanceAdapter ? DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE : DXGI_GPU_PREFERENCE_UNSPECIFIED;
			for (uint32 AdaptorIndex = 0u; SUCCEEDED(Factory6->EnumAdapterByGpuPreference(AdaptorIndex, GpuPreference, IID_PPV_ARGS(&Adaptor))); ++AdaptorIndex)
			{
				DXGI_ADAPTER_DESC1 Desc;
				Adaptor->GetDesc1(&Desc);

				if (Desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
				{
					// Skip software adapter. 
					continue;
				}

				// todo: Feature level 11_0 is safe enough?
				if (SUCCEEDED(D3D12CreateDevice(Adaptor.Get(), D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr)))
				{
					break;
				}
			}
		}

		if (Adaptor.Get() == nullptr)
		{
			for (uint32 AdaptorIndex = 0; SUCCEEDED(FactoryPtr->EnumAdapters1(AdaptorIndex, &Adaptor)); ++AdaptorIndex)
			{
				DXGI_ADAPTER_DESC1 Desc;
				Adaptor->GetDesc1(&Desc);

				if (Desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
				{
					// Skip software adapter. 
					continue;
				}

				if (SUCCEEDED(D3D12CreateDevice(Adaptor.Get(), D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr)))
				{
					break;
				}
			}
		}

		*OutAdaptorPtr = Adaptor.Detach();
	}

	ComPtr<ID3DBlob> HRenderPipelineUtils::CompileShaderFromFile(const HString& ShaderPath, const char* EntryPoint, const char* TargetShaderModel)
	{
		uint32 CompileFlags = 0u;
#if _DEBUG
		CompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
		HRESULT hr = S_OK;

		ComPtr<ID3DBlob> ByteCode = nullptr;
		ComPtr<ID3DBlob> Errors;
		hr = D3DCompileFromFile(ShaderPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			EntryPoint, TargetShaderModel, CompileFlags, 0, &ByteCode, &Errors);

		if (Errors != nullptr)
		{
			OutputDebugStringA((char*)Errors->GetBufferPointer());
		}

		ThrowIfFailed(hr);
		return ByteCode;
	}

	ComPtr<ID3D12Resource> HD3DResourceUtils::CreateDefaultBuffer(ID3D12Device* Device, ID3D12GraphicsCommandList* CommandList, const void* InitData, uint64 ByteSize, ComPtr<ID3D12Resource>& UploadBuffer)
	{
		ComPtr<ID3D12Resource> DefaultBuffer;

		{
			auto DefaultHeapType = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
			auto Buffer = CD3DX12_RESOURCE_DESC::Buffer(ByteSize);

			// ���� DefaultBuffer ���ҽ� �Ҵ�.
			ThrowIfFailed(Device->CreateCommittedResource(
				&DefaultHeapType,
				D3D12_HEAP_FLAG_NONE,
				&Buffer,
				D3D12_RESOURCE_STATE_COMMON,
				nullptr,
				IID_PPV_ARGS(DefaultBuffer.GetAddressOf())
			));
		}

		// CPU Memory�� ����Ʈ ���ۿ� �Űܴ�� ����, �߰� �ٸ� ������ ���� ���ε� ���� ������.
		{
			auto UploadHeapType = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
			auto Buffer = CD3DX12_RESOURCE_DESC::Buffer(ByteSize);
			ThrowIfFailed(Device->CreateCommittedResource(
				&UploadHeapType,
				D3D12_HEAP_FLAG_NONE,
				&Buffer,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(UploadBuffer.GetAddressOf())
			));
		}

		// ����Ʈ ���ۿ� � �����͸� ���� �������� ����
		D3D12_SUBRESOURCE_DATA SubresourceData =
		{
			.pData = InitData,
			.RowPitch = static_cast<LONG_PTR>(ByteSize),
			.SlicePitch = static_cast<LONG_PTR>(ByteSize)
		};

		// �����͸� ����Ʈ ���ۿ� �����ϵ��� �����صд�. ���� ���������� UpdateSubresources �Լ��� CPU Memory�� �߰��ܰ��� ���ε� ���� �Ű��ش�.
		// �� ���Ŀ� ID3D12CommandList::CopySubresourceRegion�� �̿��� ���ε� ������ GPU �޸𸮷� �����Ͱ� �Ű��� ���̴�.
		auto CommonToCopyDestTransitionBarrier = CD3DX12_RESOURCE_BARRIER::Transition(DefaultBuffer.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
		CommandList->ResourceBarrier(1, &CommonToCopyDestTransitionBarrier);

		UpdateSubresources<1>(CommandList, DefaultBuffer.Get(), UploadBuffer.Get(), 0, 0, 1, &SubresourceData);

		auto CopyDestToCommonTransitionBarrier = CD3DX12_RESOURCE_BARRIER::Transition(DefaultBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);
		CommandList->ResourceBarrier(1, &CopyDestToCommonTransitionBarrier);

		return DefaultBuffer;
	}
}
