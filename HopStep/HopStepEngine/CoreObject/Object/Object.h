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

		// IGCObject interfaces
		virtual uint32 GetGCPoolIndex() const override final { return PoolIndex; }
		virtual void SetGCPoolIndex(uint32 Index) override final { PoolIndex = Index; }
		virtual TArray<IGCObject*> GetGCProperties() override;
		virtual bool IsGCRoot() const override;
		virtual bool GetGCMark() const override final;
		virtual void SetGCMark(bool bMark) override final;
		virtual void SetSerialNumber(uint32 SerialNumber) override;
		virtual uint32 GetSerialNumber() const override;

	protected:

		uint32 PoolIndex = IGCObject::InvalidGCPoolIndex;
		uint32 SerialNumber = IGCObject::InvalidGCPoolIndex;
		bool bMarked = false;

	};
}
