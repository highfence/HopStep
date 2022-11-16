#pragma once
#include "..\PrimitiveTypeDefines.h"
#include "..\HopStepOverrides.h"

namespace HopStep
{
	class ICommandExecutable
	{
	public:

		virtual ~ICommandExecutable() {};

		// Todo: Add param world
		virtual bool Execute(const HChar* InCommand, class IOutputDevice* InDevice) = 0;
	};
}