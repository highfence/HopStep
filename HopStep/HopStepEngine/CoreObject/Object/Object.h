#pragma once
#include "..\..\Core\HopStepCore.h"
#include "..\Reflection\ReflectionMarco.h"
#include "Intermediate\Object.generated.h"

HCLASS();
class HObject
{
	DECLARE_CLASS_BODY(HObject);

public:

	HPROPERTY();
	int32 a;

};
