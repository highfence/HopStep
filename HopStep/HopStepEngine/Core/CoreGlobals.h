#pragma once
#include "HopStepOverrides.h"
#include "PrimitiveTypeDefines.h"

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

	/**
	 * Client Section
	 */
	static int32 ClientWidth = 1280;
	static int32 ClientHeight = 720;
}