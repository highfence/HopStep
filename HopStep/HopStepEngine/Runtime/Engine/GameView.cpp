#include "GameView.h"
#define GAME_VIEW_DEBUG 0

namespace HopStep
{
	HGameView::HGameView() :
		PressState{ },
		Position(0, 0, 0),
		MoveSpeed(20.0f),
		TurnSpeed(::DirectX::XM_PIDIV2),
		Yaw(::DirectX::XM_PI),
		Pitch(0.0f),
		LookDirection(0, 0, -1),
		UpDirection(0, 1, 0)
	{
	}

	void HGameView::Init(XMFLOAT3 InPosition)
	{
		Position = InPosition;
		Reset();
	}

	void HGameView::Update(float DeltaTime)
	{
		XMFLOAT3 Move(0, 0, 0);

		// Calculate move state
		{
			if (PressState.A) Move.x -= 1.0f;
			if (PressState.D) Move.x += 1.0f;
			if (PressState.W) Move.z -= 1.0f;
			if (PressState.S) Move.z += 1.0f;

			if (fabs(Move.x) > 0.1f && fabs(Move.z) > 0.1f)
			{
				XMVECTOR Vector = ::DirectX::XMVector3Normalize(XMLoadFloat3(&Move));
				Move.x = ::DirectX::XMVectorGetX(Vector);
				Move.z = ::DirectX::XMVectorGetZ(Vector);
			}
		}

		// Move camera to model space
		{
			const float MoveInterval = MoveSpeed * DeltaTime;
			const float X = Move.x * -cosf(Yaw) - Move.z * sinf(Yaw);
			const float Z = Move.x * sinf(Yaw) - Move.z * cosf(Yaw);

			Position.x += X * MoveInterval;
			Position.z += Z * MoveInterval;
		}

		// Determine look direction
		{
			float R = cosf(Pitch);
			LookDirection.x = R * sinf(Yaw);
			LookDirection.y = sinf(Pitch);
			LookDirection.z = R * cosf(Yaw);
		}

#if GAME_VIEW_DEBUG
		HString Desc = ToString();
		OutputDebugString(Desc.c_str());
#endif
	}

	void HGameView::OnKeyDown(uint64* Key)
	{
		switch (reinterpret_cast<WPARAM>(Key))
		{
		case 'W':
			PressState.W = true;
			break;

		case 'A':
			PressState.A = true;
			break;

		case 'S':
			PressState.S = true;
			break;

		case 'D':
			PressState.D = true;
			break;

		case VK_ESCAPE:
			Reset();
			break;
		}
	}

	void HGameView::OnKeyUp(uint64* Key)
	{
		switch (reinterpret_cast<WPARAM>(Key))
		{
		case 'W':
			PressState.W = false;
			break;

		case 'A':
			PressState.A = false;
			break;

		case 'S':
			PressState.S = false;
			break;

		case 'D':
			PressState.D = false;
			break;
		}

	}

	XMVECTOR HGameView::GetPosition() const
	{
		return ::DirectX::XMLoadFloat3(&Position);
	}

	XMFLOAT3 HGameView::GetPosition3f() const
	{
		return Position;
	}

	XMMATRIX HGameView::GetViewMatrix() const
	{
		return ::DirectX::XMMatrixLookToRH(XMLoadFloat3(&Position), XMLoadFloat3(&LookDirection), XMLoadFloat3(&UpDirection));
	}

	XMMATRIX HGameView::GetProjectionMatrix(float FOV, float AspectRatio, float NearPlane, float FarPlane) const
	{
		return ::DirectX::XMMatrixPerspectiveFovRH(FOV, AspectRatio, NearPlane, FarPlane);
	}

	HString HGameView::ToString() const
	{
		HString Desc;
		Desc.append(TEXT("PressState:\n"));
		Desc.append(std::format(TEXT("\tW: {}\n"), PressState.W ? TEXT("On") : TEXT("Off")));
		Desc.append(std::format(TEXT("\tA: {}\n"), PressState.A ? TEXT("On") : TEXT("Off")));
		Desc.append(std::format(TEXT("\tS: {}\n"), PressState.S ? TEXT("On") : TEXT("Off")));
		Desc.append(std::format(TEXT("\tD: {}\n"), PressState.D ? TEXT("On") : TEXT("Off")));
		Desc.append(std::format(TEXT("\tPos: {},{},{}"), Position.x, Position.y, Position.z));
		return Desc;
	}

	void HGameView::Reset()
	{
		Position = { 0, 0, 0 };
		Yaw = ::DirectX::XM_PI;
		Pitch = 0.0f;
		LookDirection = { 0, 0, -1 };
	}
}