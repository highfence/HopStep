#pragma once
#include "SceneInterface.h"

namespace HopStep
{
	class HScene : public HSceneInterface
	{
	public:

		// Inherited via HSceneInterface
		virtual void AddPrimitive(class HPrimitiveComponent* Primitive) override;

		virtual void RemovePrimitive(class HPrimitiveComponent* Primitive) override;

	};
}