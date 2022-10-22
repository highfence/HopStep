#pragma once
#include "Core\HopStepCore.h"
#include "CoreObject\Reflection\ReflectionMacro.h"
#include "ObjectBase.h"
#include "Intermediate\Object.generated.h"

#define CONCAT(A,B,C,D) A##B##C##D
#define TEST CONCAT(CURRENT_FILE_ID,_,__LINE__,_Generated_Function_Declare)

HCLASS();
class HObject : public HObjectBase
{
	TEST;
	DECLARE_CLASS_BODY(HObject);

public:

	HPROPERTY();
	int32 a;

};
