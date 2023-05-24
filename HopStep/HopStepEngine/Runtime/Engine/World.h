#pragma once
#include "Core\CoreExport.h"
#include "CoreObject\CoreObjectExport.h"
#include "Level.h"
#include "Intermediate\World.generated.h"

namespace HopStep
{
	HCLASS();
	class HWorld : public HObject
	{
		DECLARE_CLASS_BODY(HWorld)

	public:

		~HWorld();

		HPROPERTY();
		TObjectPtr<HLevel> PersistentLevel;

		bool InitWorld();

		void Tick(float deltaTime);

	protected:

		class HSceneInterface* Scene = nullptr;


	};
}
