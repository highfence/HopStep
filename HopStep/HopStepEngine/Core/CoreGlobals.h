#pragma once

namespace HopStep
{
	/**
	 * Engine Loop Section
	 */
	bool IsEngineExitRequested();

	void RequestEngineExit(const class HString& Reason);

	/**
	 * Engine Config Section
	 */
	extern class HEngineConfig* GConfig;
}