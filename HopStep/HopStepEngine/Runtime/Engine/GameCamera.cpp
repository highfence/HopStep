#include "GameCamera.h"

namespace HopStep
{
	HGameCamera::HGameCamera() :
		PressState{ },
		InitialPosition(0, 0, 0),
		Position(InitialPosition),
		MoveSpeed(20.0f),
		TurnSpeed(::DirectX::XM_PIDIV2),
		Yaw(::DirectX::XM_PI),
		Pitch(0.0f),
		LookDirection(0, 0, -1),
		UpDirection(0, 1, 0)
	{
	}

	void HGameCamera::Init(XMFLOAT3 InPosition)
	{
		InitialPosition = InPosition;
		Reset();
	}

	void HGameCamera::Update(float DeltaTime)
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

		// Calculate rotate state
		{
			const float RotateInterval = TurnSpeed * DeltaTime;

			if (PressState.Left) Yaw += RotateInterval;
			if (PressState.Right) Yaw -= RotateInterval;
			if (PressState.Up) Pitch += RotateInterval;
			if (PressState.Down) Pitch -= RotateInterval;

			// Preventing looking too far up or down
			Pitch = min(Pitch, ::DirectX::XM_PIDIV4);
			Pitch = max(-::DirectX::XM_PIDIV4, Pitch);
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
	}

	void HGameCamera::OnKeyDown(uint64* Key)
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

		case VK_LEFT:
			PressState.Left = true;
			break;

		case VK_RIGHT:
			PressState.Right = true;
			break;

		case VK_UP:
			PressState.Up = true;
			break;

		case VK_DOWN:
			PressState.Down = true;
			break;

		case VK_ESCAPE:
			Reset();
			break;
		}
	}

	void HGameCamera::OnKeyUp(uint64* Key)
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

		case VK_LEFT:
			PressState.Left = false;
			break;

		case VK_RIGHT:
			PressState.Right = false;
			break;

		case VK_UP:
			PressState.Up = false;
			break;

		case VK_DOWN:
			PressState.Down = false;
			break;
		}

	}

	XMMATRIX HGameCamera::GetViewMatrix()
	{
		return ::DirectX::XMMatrixLookToRH(XMLoadFloat3(&Position), XMLoadFloat3(&LookDirection), XMLoadFloat3(&UpDirection));
	}

	XMMATRIX HGameCamera::GetProjectionMatrix(float FOV, float AspectRatio, float NearPlane, float FarPlane)
	{
		return ::DirectX::XMMatrixPerspectiveFovRH(FOV, AspectRatio, NearPlane, FarPlane);
	}

	HString HGameCamera::ToString() const
	{
		HString Desc;
		Desc.append(TEXT("PressState:\n"));
		Desc.append(std::format(TEXT("\tW: {}\n"), PressState.W ? TEXT("On") : TEXT("Off")));
		Desc.append(std::format(TEXT("\tA: {}\n"), PressState.A ? TEXT("On") : TEXT("Off")));
		Desc.append(std::format(TEXT("\tS: {}\n"), PressState.S ? TEXT("On") : TEXT("Off")));
		Desc.append(std::format(TEXT("\tD: {}\n"), PressState.D ? TEXT("On") : TEXT("Off")));

		Desc.append(std::format(TEXT("\tLeft: {}\n"), PressState.Left ? TEXT("On") : TEXT("Off")));
		Desc.append(std::format(TEXT("\tRight: {}\n"), PressState.Right ? TEXT("On") : TEXT("Off")));
		Desc.append(std::format(TEXT("\tUp: {}\n"), PressState.Up ? TEXT("On") : TEXT("Off")));
		Desc.append(std::format(TEXT("\tDown: {}\n"), PressState.Down ? TEXT("On") : TEXT("Off")));
		return Desc;
	}

	void HGameCamera::Reset()
	{
		Position = InitialPosition;
		Yaw = ::DirectX::XM_PI;
		Pitch = 0.0f;
		LookDirection = { 0, 0, -1 };
	}
}