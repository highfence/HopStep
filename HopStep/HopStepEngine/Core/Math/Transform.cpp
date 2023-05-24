#include "Transform.h"

namespace HopStep
{
	const HTransform HTransform::Identity = HTransform(HQuat(0.f, 0.f, 0.f, 1.f), HVector(0.f), HVector(1.f));

}