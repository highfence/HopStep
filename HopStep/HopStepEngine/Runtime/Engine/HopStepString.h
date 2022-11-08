#pragma once
#include "..\..\Core\CoreExport.h"
#include "..\..\CoreObject\CoreObjectExport.h"
#include "..\..\Core\Misc\OutputDevice.h"

namespace HopStep
{
	class HStringOutputDevice : public IOutputDevice
	{
	public:

		virtual void Serialize(const HChar* Value, LogType Verbosity, const class HName& Catergory) override;
	};
}
