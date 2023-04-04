#pragma once

namespace HopStep
{
	class HSceneInterface
	{
	public:

		HSceneInterface();

		virtual ~HSceneInterface();

		virtual void AddPrimitive(class HPrimitiveComponent* Primitive) = 0;

		virtual	void RemovePrimitive(class HPrimitiveComponent* Primitive) = 0;

	protected:


	};
}