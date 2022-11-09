#pragma once
#include "..\..\Core\CoreExport.h"
#include "..\..\CoreObject\CoreObjectExport.h"
#include "..\..\Core\Misc\OutputDevice.h"

namespace HopStep
{
	namespace HCharExtention
	{
		const HChar* EmptyChar = TEXT("");
	}

	namespace HStringExtension
	{
		const HString EmptyString = HString(EmptyChar);
	}

	class HStringOutputDevice : public IOutputDevice
	{
	public:

		HStringOutputDevice(const HChar* OutputDeviceName = HCharExtention::EmptyChar)
			: Value(OutputDeviceName)
		{

		}

		virtual void Serialize(const HChar* InValue, LogType Verbosity, const class HName& Catergory) override;

		virtual HString& operator+=(const HString& Other)
		{
			return Value += Other;
		}

	private:

		HString Value;
	};
}
