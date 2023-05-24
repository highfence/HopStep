#include "HopStep.h"
#include "Runtime\Engine\StaticMesh.h"

using namespace HopStep;

void HStaticMesh::__Fill_Class_Property_HStaticMesh(HClass* InStaticClass)
{
	HStructBuilder::SetSuper<HObject>(InStaticClass);
}

IMPLEMENT_CLASS(HStaticMesh);
