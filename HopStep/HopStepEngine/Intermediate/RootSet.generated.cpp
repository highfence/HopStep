#include "HopStep.h"
#include "RootSet.generated.h"
#include "CoreObject\Object\RootSet.h"

using namespace HopStep;

void HRootSet::__Fill_Class_Property_HRootSet(HClass* InStaticClass)
{
	HStructBuilder::AddProperty<HRootSet, TArray<HObject*>, HArrayProperty>(InStaticClass, TEXT("Childs"), &HRootSet::Childs);
	HStructBuilder::SetSuper<HObject>(InStaticClass);
}

IMPLEMENT_CLASS(HRootSet);
