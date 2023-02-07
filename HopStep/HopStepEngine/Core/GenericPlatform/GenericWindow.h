#pragma once
#include "..\PrimitiveTypeDefines.h"

namespace HopStep
{
	class HGenericWindow
	{
	public:

		virtual ~HGenericWindow() {};

		virtual uint32 GetClientWidth() = 0;
		virtual uint32 GetClientHeight() = 0;
	};
}