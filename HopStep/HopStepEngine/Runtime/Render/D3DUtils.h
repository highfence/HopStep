#pragma once
#include "DirectXIncludes.h"

namespace HopStep
{
	class HDirectXException
	{
	public:

		HDirectXException() = default;
		HDirectXException(HRESULT HR, const HString& FunctionName, const HString& FileName, int32 LineNumber);

		HString ToString() const;

	protected:

		HRESULT ErrorCode = S_OK;
		HString FunctionName;
		HString FileName;
		int32 LineNumber = -1;
	};
}

inline HopStep::HString AnsiToHString(const std::string& Str)
{
	HopStep::HChar Buffer[512];
	MultiByteToWideChar(CP_ACP, 0, Str.c_str(), -1, Buffer, 512);
	return HopStep::HString(Buffer);
}

#ifndef ThrowIfFailed 
#define ThrowIfFailed(x) \
{ \
	HRESULT _Hr = (x); \
	HopStep::HString _FileName = AnsiToHString(__FILE__); \
	if (FAILED(_Hr)) { throw ::HopStep::HDirectXException(_Hr, L#x, _FileName, __LINE__); } \
}
#endif

#ifndef ComRelease
#define ComRelease(x) { if (x) { x->Release(); x = nullptr; } }
#endif
