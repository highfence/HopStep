#pragma once
#include "Core/CoreExport.h"
#include "Core/Logger/LoggerBase.h"

namespace HopStep
{
	/**
	 * Output device interface
	 */
	class IOutputDevice
	{
	public:

		/**
		 * todo : string view to HName
		 */
		virtual void Serialize(const HChar* Value, LogType Verbosity, const class HName& Catergory) = 0;
	};
}
