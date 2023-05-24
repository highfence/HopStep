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

		HVector(float InX, float InY, float InZ = 0.f)
			: X{ InX }
			, Y{ InY }
			, Z{ InZ }
		{
		}

		HVector(float InF)
			: X{ InF }
			, Y{ InF }
			, Z{ InF }
		{
		}

		HVector()
			: X{ 0.f }
			, Y{ 0.f }
			, Z{ 0.f }
		{}

		HVector operator+(const HVector& Other) const
		{
			return HVector(X + Other.X, Y + Other.Y, Z + Other.Z);
		}

		HVector operator-(const HVector& Other) const
		{
			return HVector(X - Other.X, Y - Other.Y, Z - Other.Z);
		}

		HVector operator*(const HVector& Other) const
		{
			return HVector(X * Other.X, Y * Other.Y, Z * Other.Z);
		}

		HVector operator/(const HVector& Other) const
		{
			return HVector(X / Other.X, Y / Other.Y, Z / Other.Z);
		}

		HVector operator*(float Scale) const
		{
			return HVector(X * Scale, Y * Scale, Z * Scale);
		}

		HVector operator/(float Scale) const
		{
			const float RScale = 1.f / Scale;
			return HVector(X * RScale, Y * RScale, Z * RScale);
		}

		HVector operator-() const
		{
			return HVector(-X, -Y, -Z);
		}

		HVector operator+=(const HVector& Other)
		{
			X += Other.X;
			Y += Other.Y;
			Z += Other.Z;
			return *this;
		}

		HVector operator-=(const HVector& Other)
		{
			X -= Other.X;
			Y -= Other.Y;
			Z -= Other.Z;
			return *this;
		}

		HVector operator*=(const HVector& Other)
		{
			X *= Other.X;
			Y *= Other.Y;
			Z *= Other.Z;
			return *this;
		}

		HVector operator/=(const HVector& Other)
		{
			X /= Other.X;
			Y /= Other.Y;
			Z /= Other.Z;
			return *this;
		}

		HVector operator*=(float Scale)
		{
			X *= Scale;
			Y *= Scale;
			Z *= Scale;
			return *this;
		}

		HVector operator/=(float Scale)
		{
			const float RScale = 1.f / Scale;
			X *= RScale;
			Y *= RScale;
			Z *= RScale;
			return *this;
		}

		bool operator==(const HVector& Other) const
		{
			return X == Other.X && Y == Other.Y && Z == Other.Z;
		}

		bool operator!=(const HVector& Other) const
		{
			return X != Other.X || Y != Other.Y || Z != Other.Z;
		}

		HVector operator+(float A) const
		{
			return HVector(X + A, Y + A, Z + A);
		}

		HVector operator-(float A) const
		{
			return HVector(X - A, Y - A, Z - A);
		}

	public:

		static const HVector ZeroVector;

		static const HVector OneVector;
	};

}