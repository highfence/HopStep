#pragma once
#include "..\CoreExport.h"
#include "..\Logger\LoggerBase.h"

namespace HopStep
{
	/**
	 * Output device interface
	 */
	class IOutputDevice
	{
	public:

		/**
		 * 
		 */
		virtual void Serialize(const HChar* Value, LogType Verbosity, const class HName& Catergory) = 0;
	};
}
