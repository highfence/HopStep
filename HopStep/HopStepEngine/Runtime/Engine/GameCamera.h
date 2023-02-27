#pragma once
#include "Core/GenericPlatform/GenericApplicationMessageHandler.h"
#include "Runtime/Render/DirectXIncludes.h"

namespace HopStep
{
	class HGameCamera : public IKeyHandleable
	{
	public:

		HGameCamera();

		void Init(XMFLOAT3 InPosition);
		void Update(float DeltaTime);

		void OnKeyDown(uint64* Key);
		void OnKeyUp(uint64* Key);

		XMMATRIX GetViewMatrix();
		XMMATRIX GetProjectionMatrix(float FOV, float AspectRatio, float NearPlane = 1.0f, float FarPlane = 1000.0f);

	protected:

		void Reset();

		// Todo: Temp
		struct HKeyPressed
		{
			bool W;
			bool A;
			bool S;
			bool D;

			bool Left;
			bool Right;
			bool Up;
			bool Down;
		};

		HKeyPressed PressState;

		XMFLOAT3 InitialPosition;
		XMFLOAT3 Position;

		float MoveSpeed;
		float TurnSpeed;

		float Yaw;
		float Pitch;

		XMFLOAT3 LookDirection;
		XMFLOAT3 UpDirection;
	};
}