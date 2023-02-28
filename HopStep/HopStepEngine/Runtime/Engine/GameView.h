#pragma once
#include "Core/GenericPlatform/GenericApplicationMessageHandler.h"
#include "Runtime/Render/DirectXIncludes.h"

namespace HopStep
{
	class HGameView : public IInputHandleable
	{
	public:

		HGameView();

		void Init(XMFLOAT3 InPosition);
		void Update(float DeltaTime);

		void OnKeyDown(uint64* Key);
		void OnKeyUp(uint64* Key);

		XMVECTOR GetPosition() const;
		XMFLOAT3 GetPosition3f() const;

		XMMATRIX GetViewMatrix() const;
		XMMATRIX GetProjectionMatrix(float FOV, float AspectRatio, float NearPlane = 1.0f, float FarPlane = 1000.0f) const;

		HString ToString() const;

	protected:

		void Reset();

		// Todo: Temp
		struct HKeyPressed
		{
			bool W;
			bool A;
			bool S;
			bool D;
		};

		HKeyPressed PressState;

		XMFLOAT3 Position;

		float MoveSpeed;
		float TurnSpeed;

		float Yaw;
		float Pitch;

		XMFLOAT3 LookDirection;
		XMFLOAT3 UpDirection;
	};
}