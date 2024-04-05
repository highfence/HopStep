#pragma once

namespace HopStep
{
	class HSceneInterface
	{
	public:

		static HSceneInterface* CreateScene();

		HSceneInterface();

		virtual ~HSceneInterface();

		virtual void AddPrimitive(class HPrimitiveComponent* Primitive) = 0;

		virtual	void RemovePrimitive(class HPrimitiveComponent* Primitive) = 0;

		virtual void Render() const = 0;

	protected:


	};
}