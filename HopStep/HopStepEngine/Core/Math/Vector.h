#pragma once

namespace HopStep
{
	/**
	 * A vector in 3-D space composed of components (X, Y, Z) with floating point precision.
	 */
	struct HVector
	{
	public:

		float X;

		float Y;

		float Z;


	public:

		static const HVector ZeroVector;

		static const HVector OneVector;
	};

}