#pragma once

namespace HopStep
{
	class HApp
	{
	public:

		static double GetCurrentAppTime();

		static void SetCurrentTime(double InTime);

		static double GetDeltaTime();

		static void SetDeltaTime(double InSeconds);

		static class HGenericApplication* GetApp() { return GApp; }

		static class HGenericApplication* GApp;

	protected:

		static double CurrentTime;

		static double DeltaTime;

	};
}