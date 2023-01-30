#pragma once
#include "..\GenericPlatform\GenericApplication.h"
#include "..\CoreExport.h"
#include "WindowsSystemIncludes.h"

namespace HopStep
{
	class HWindowsApplication : public HGenericApplication
	{
	public:

		HWindowsApplication(HINSTANCE hInstanceHandle);

		virtual void SetWindow(TSharedPtr<class HGenericWindow> Window) override;

		virtual TSharedPtr<class HGenericWindow> GetWindow() override;

		virtual void PumpMessages(float DeltaTime) override;

	protected:

		static LRESULT CALLBACK AppWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		HINSTANCE InstanceHandle;

		TSharedPtr<HGenericWindow> NativeWindow;
	};
}