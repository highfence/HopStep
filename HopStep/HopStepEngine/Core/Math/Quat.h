#pragma once

namespace HopStep
{
	/**
	* Floating point quaternion that can represent a rotation about an axis in 3-D space.
	* The X, Y, Z, W components also double as the Axis/Angle format.
	*
	* Order matters when composing quaternions: C = A * B will yield a quaternion C that logically
	* first applies B then A to any subsequent transformation (right first, then left).
	* Note that this is the opposite order of FTransform multiplication.
	*
	* Example: LocalToWorld = (LocalToWorld * DeltaRotation) will change rotation in local space by DeltaRotation.
	* Example: LocalToWorld = (DeltaRotation * LocalToWorld) will change rotation in world space by DeltaRotation.
	*/
	struct HQuat
	{
		float X;

		float Y;

		float Z;

		float W;
	};

}