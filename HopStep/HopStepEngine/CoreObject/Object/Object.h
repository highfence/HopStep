#pragma once
#include "GCInterface.h"
#include "ObjectBase.h"
#include "..\Reflection\ReflectionMacro.h"
#include "..\..\Core\CoreExport.h"
#include "..\..\Intermediate\Object.generated.h"

namespace HopStep
{
	HCLASS();
	class HObject : public HObjectBase, public IGCObject
	{
		DECLARE_CLASS_BODY(HObject);

	public:

		virtual uint32 GetPoolIndex() const override final { return PoolIndex; }
		virtual void SetPoolIndex(uint32 Index) override final { PoolIndex = Index; }

	protected:

		uint32 PoolIndex = IGCObject::InvalidPoolIndex;
	};
}
