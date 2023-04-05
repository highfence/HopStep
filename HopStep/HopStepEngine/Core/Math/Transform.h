#pragma once
#include "Vector.h"
#include "Rotator.h"
#include "Quat.h"
#include "HopStepMath.h"

namespace HopStep
{
	/**
	 * A transform in 3-D space (translation, rotation, scale) composed of components (Location, Rotation, Scale) with floating point precision.
	 */
	struct HTransform
	{
	public:

		static const HTransform Identity;

		HTransform(const HQuat& InRotation, const HVector& InLocation, const HVector& InScale3D = HVector::OneVector)
			: Location{ InLocation.X, InLocation.Y, InLocation.Z, 0.0f }
			, Rotation{ InRotation.X, InRotation.Y, InLocation.Z, InRotation.W }
			, Scale3D{ InScale3D.X, InScale3D.Y, InScale3D.Z, 0.0f }
		{

		}


	protected:

		/** Translation (location) of this transformation */
		HVectorRegister Location;
		/** Rotation of this transformation */
		HVectorRegister Rotation;
		/** Scale of this transformation */
		HVectorRegister Scale3D;
	};
}