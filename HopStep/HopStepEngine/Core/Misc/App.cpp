#include "App.h"

namespace HopStep
{
	double HApp::CurrentTime = 0.0;
	double HApp::DeltaTime = 1 / 30.0;

	double HApp::GetCurrentTime()
	{
		return CurrentTime;
	}

	void HApp::SetCurrentTime(double InTime)
	{
		CurrentTime = InTime;
	}

	double HApp::GetDeltaTime()
	{
		return DeltaTime;
	}

	void HApp::SetDeltaTime(double InSeconds)
	{
		DeltaTime = InSeconds;
	}
}