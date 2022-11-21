#pragma once
#include "..\..\Core\CoreExport.h"
#include "..\Reflection\ReflectionMacro.h"
#include "GCInterface.h"
#include "ObjectBase.h"
#include "..\..\Intermediate\Object.generated.h"

namespace HopStep
{
	HCLASS();
	class HObject : public HObjectBase, public IGCObject
	{
		DECLARE_CLASS_BODY(HObject);

	public:

	};
}
