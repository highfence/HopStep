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

		HTransform(const HQuat& InRotation, const HVector& InLocation, const HVector& InScale3D = HVector::OneVector)
			: Location{ InLocation.X, InLocation.Y, InLocation.Z, 0.0f }
			, Rotation{ InRotation.X, InRotation.Y, InLocation.Z, InRotation.W }
			, Scale3D{ InScale3D.X, InScale3D.Y, InScale3D.Z, 0.0f }
		{

		}

		HTransform()
			: Location(0.0f, 0.0f, 0.0f, 0.0f)
			, Rotation(0.0f, 0.0f, 0.0f, 0.0f)
			, Scale3D(0.0f, 0.0f, 0.0f, 0.0f)
		{
		}

		static const HTransform Identity;

		HVector GetLocation() const
		{
			return HVector(Location.V[0], Location.V[1], Location.V[2]);
		}

		HRotator GetRotation() const
		{
			return HRotator(Rotation.V[0], Rotation.V[1], Rotation.V[2]);
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