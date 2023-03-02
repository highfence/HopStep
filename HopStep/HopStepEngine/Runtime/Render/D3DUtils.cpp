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
}
