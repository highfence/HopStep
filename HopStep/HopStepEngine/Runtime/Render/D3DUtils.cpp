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
}
