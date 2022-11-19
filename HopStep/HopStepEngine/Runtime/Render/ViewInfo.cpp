#include "ViewInfo.h"

namespace HopStep
{
	HViewInfo::HViewInfo()
		: Position(0, 0, 0)
		, Rotation(0, 0, 0)
		, ViewMatrix()
	{
	}

	HViewInfo::~HViewInfo()
	{
	}

	void HViewInfo::SetPosition(float X, float Y, float Z)
	{
		Position.x = X;
		Position.y = Y;
		Position.z = Z;
	}

	void HViewInfo::SetRotation(float X, float Y, float Z)
	{
		Rotation.x = X;
		Rotation.y = Y;
		Rotation.z = Z;
	}

	XMFLOAT3 HViewInfo::GetPosition()
	{
		return Position;
	}

	XMFLOAT3 HViewInfo::GetRotation()
	{
		return Rotation;
	}

	void HViewInfo::UpdateViewMatrix()
	{
		XMVECTOR Up = XMVECTOR{0, 1, 0};
		XMVECTOR LookAt = XMVECTOR{0, 0, 1};
		XMVECTOR Pos = XMVECTOR{Position.x, Position.y, Position.z};
		
		constexpr float Radians = 0.0174532925f;
		float Pitch = Rotation.x * Radians;
		float Yaw = Rotation.y * Radians;
		float Roll = Rotation.z * Radians;

		XMMATRIX RotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(Pitch, Yaw, Roll);

		LookAt = DirectX::XMVector3TransformCoord(LookAt, RotationMatrix);
		Up = DirectX::XMVector3TransformCoord(Up, RotationMatrix);

		LookAt = DirectX::XMVectorAdd(LookAt, Pos);
		ViewMatrix = DirectX::XMMatrixLookAtLH(Pos, LookAt, Up);
	}

	XMMATRIX HViewInfo::GetViewMatrix()
	{
		return ViewMatrix;
	}
}
