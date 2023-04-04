#pragma once
#include "Vector.h"
#include "Rotator.h"

namespace HopStep
{
	/**
	 * A transform in 3-D space (translation, rotation, scale) composed of components (Location, Rotation, Scale) with floating point precision.
	 */
	struct HTransform
	{
	public:

		HVector Location;

		HRotator Rotation;

		HVector Scale;
	};
}