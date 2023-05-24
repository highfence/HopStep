#include "HopStep.h"
#include "Runtime\Engine\Level.h"

using namespace HopStep;

void HLevel::__Fill_Class_Property_HLevel(HClass* InStaticClass)
{
	HStructBuilder::SetSuper<HObject>(InStaticClass);
}

IMPLEMENT_CLASS(HLevel);
