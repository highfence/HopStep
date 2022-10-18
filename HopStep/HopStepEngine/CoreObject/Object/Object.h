#pragma once
#include "Core\HopStepCore.h"
#include "CoreObject\Reflection\ReflectionMarco.h"
#include "ObjectBase.h"
#include "Intermediate\Object.generated.h"

HCLASS();
class HObject : public HObjectBase
{
	DECLARE_CLASS_BODY(HObject);

public:

	HPROPERTY();
	int32 a;

};
