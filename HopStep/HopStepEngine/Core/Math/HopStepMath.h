#pragma once

namespace HopStep
{
	struct HVectorRegister
	{
		float V[4];

		HVectorRegister(float V0, float V1, float V2, float V3)
		{
			V[0] = V0;
			V[1] = V1;
			V[2] = V2;
			V[3] = V3;
		}
	};
}