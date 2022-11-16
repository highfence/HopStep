#pragma once
#include "HopStepOverrides.h"

namespace HopStep
{
	/**
	 * Engine Loop Section
	 */
	bool IsEngineExitRequested();

	void RequestEngineExit(const HString& Reason);

	/**
	 * Engine Config Section
	 */
	extern class HEngineConfig* GConfig;

	/**
	 * 	Engine Time
	 */
	extern double GStartTime;
}