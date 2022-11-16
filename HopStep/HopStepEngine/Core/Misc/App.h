#pragma once

namespace HopStep
{
	class HApp
	{
	public:

		static double GetCurrentTime();

		static void SetCurrentTime(double InTime);

		static double GetDeltaTime();

		static void SetDeltaTime(double InSeconds);

	protected:

		static double CurrentTime;

		static double DeltaTime;
	};
}