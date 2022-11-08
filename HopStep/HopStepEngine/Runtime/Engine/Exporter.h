#pragma once
#include "HopStep.h"

namespace HopStep
{
	class HExporter
	{
	public:

		/**
		 * Todo : Make find exporter and use it.
		 */
		static void ExportToOutputDevice(const class IOutputDevice* DeviceInterface, const class HObject* Object);

	};
}