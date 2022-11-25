#include "HopStep.h"
#include "RootSet.generated.h"
#include "CoreObject\Object\RootSet.h"

using namespace HopStep;

void HRootSet::__Fill_Class_Property_HRootSet(HClass* InStaticClass)
{
	HStructBuilder::SetSuper<HObject>(InStaticClass);
}

IMPLEMENT_CLASS(HRootSet);
