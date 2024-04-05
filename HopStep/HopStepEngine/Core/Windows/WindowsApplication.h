#pragma once
#include "..\GenericPlatform\GenericApplication.h"
#include "..\CoreExport.h"
#include "WindowsSystemIncludes.h"
#include "WindowsApplicationMessageHandler.h"

namespace HopStep
{
	class HWindowsApplication : public HGenericApplication
	{
	public:

		HWindowsApplication(HINSTANCE hInstanceHandle);

		virtual void SetWindow(TSharedPtr<class HGenericWindow> Window) override;

		virtual TSharedPtr<HGenericWindow> GetWindow() override;

		virtual void PumpMessages(float DeltaTime) override;

		virtual TSharedPtr<HGenericApplicationMessageHandler> GetMessageHandler() override;

		virtual HDisplayBuffer* GetDisplayBuffer() override;

		virtual uint32 GetFrameNumber() override { return FrameNumber; }
		
	protected:

		static LRESULT CALLBACK AppWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		HINSTANCE InstanceHandle;

		TSharedPtr<HGenericWindow> NativeWindow;

		TSharedPtr<HGenericApplicationMessageHandler> MessageHander;

		uint32 FrameNumber = 0u;
	};
}