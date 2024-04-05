#pragma once
#include "Core/CoreExport.h"
#include "SceneInterface.h"

namespace HopStep
{
	class HScene : public HSceneInterface
	{
	public:

		HScene();

		// Inherited via HSceneInterface
		virtual void AddPrimitive(class HPrimitiveComponent* Primitive) override;

		virtual void RemovePrimitive(class HPrimitiveComponent* Primitive) override;

		virtual void Render() const override;

	private:

		// Todo: we must divide renderer class from scene
	};
}