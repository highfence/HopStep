#pragma once
#include "..\CoreStandardIncludes.h"
#include "..\HopStepOverrides.h"

namespace HopStep
{
	class HDisplayBuffer
	{
	public:

		TArray<uint32> FrameBuffer;

		bool IsValid() const { return FrameBuffer.size() > 0; }
		uint32* GetCanvas() { return FrameBuffer.data(); }
	};

	class HGenericApplication
	{
	public:

		virtual ~HGenericApplication() {};

		virtual void PumpMessages(float DeltaTime) = 0;

		virtual void SetWindow(TSharedPtr<class HGenericWindow> Window) = 0;

		virtual TSharedPtr<class HGenericWindow> GetWindow() = 0;

		virtual TSharedPtr<class HGenericApplicationMessageHandler> GetMessageHandler() = 0;

		virtual HDisplayBuffer* GetDisplayBuffer() = 0;

		virtual uint32 GetFrameNumber() = 0;
	};
}
