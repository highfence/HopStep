#pragma once
#include "..\CoreStandardIncludes.h"

namespace HopStep
{
	class HGenericApplication
	{
	public:

		virtual ~HGenericApplication() {};

		virtual void PumpMessages(float DeltaTime) = 0;

		virtual void SetWindow(std::shared_ptr<class HGenericWindow> Window) = 0;

		virtual std::shared_ptr<class HGenericWindow> GetWindow() = 0;
	};
}
