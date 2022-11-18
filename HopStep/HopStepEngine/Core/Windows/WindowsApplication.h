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

		virtual void SetWindow(std::shared_ptr<class HGenericWindow> Window) override;

		virtual std::shared_ptr<class HGenericWindow> GetWindow() override;

		virtual void PumpMessages(float DeltaTime) override;

	protected:

		static LRESULT CALLBACK AppWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		HINSTANCE InstanceHandle;

		std::shared_ptr<HGenericWindow> NativeWindow;
	};
}