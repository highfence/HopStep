#pragma once
#include "Core\HopStepCore.h"
#include "CoreObject\Reflection\ReflectionMarco.h"
#include "Object.generated.h"

HCLASS();
class HObject
{
	DECLARE_CLASS_BODY(HObject);

public:

	HPROPERTY();
	int32 a;

};
