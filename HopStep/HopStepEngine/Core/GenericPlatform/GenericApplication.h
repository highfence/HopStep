#pragma once
#include "..\CoreStandardIncludes.h"
#include "..\HopStepOverrides.h"

namespace HopStep
{
	class HGenericApplication
	{
	public:

		virtual ~HGenericApplication() {};

		virtual void PumpMessages(float DeltaTime) = 0;

		virtual void SetWindow(TSharedPtr<class HGenericWindow> Window) = 0;

		virtual TSharedPtr<class HGenericWindow> GetWindow() = 0;

		virtual TSharedPtr<class HGenericApplicationMessageHandler> GetMessageHandler() = 0;
	};
}
