#pragma once
#include "DirectXIncludes.h"

namespace HopStep
{
	// Todo: Divide Camera from ViewInfo
	class HViewInfo
	{
	public:

		HViewInfo();
		~HViewInfo();

		void SetPosition(float, float, float);
		void SetRotation(float, float, float);

		XMFLOAT3 GetPosition();
		XMFLOAT3 GetRotation();

		void UpdateViewMatrix();
		XMMATRIX GetViewMatrix();

	protected:

		XMFLOAT3 Position;
		XMFLOAT3 Rotation;
		XMMATRIX ViewMatrix;
	};
}