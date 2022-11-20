#include "HopStep.h"
#include "World.generated.h"
#include "Runtime\Engine\World.h"

using namespace HopStep;

void HWorld::__Fill_Class_Property_HWorld(HClass* InStaticClass)
{
	HStructBuilder::SetSuper<HObject>(InStaticClass);
}

IMPLEMENT_CLASS(HWorld);
