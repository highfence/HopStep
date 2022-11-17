#pragma once
#include "..\CoreStandardIncludes.h"

namespace HopStep
{
	class HGenericApplication
	{
	public:

		virtual ~HGenericApplication() {};

		virtual void SetWindow(std::shared_ptr<class HGenericWindow> Window) = 0;

		virtual void PumpMessages(float DeltaTime) = 0;
	};
}
