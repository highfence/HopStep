#pragma once
#include "Object.h"
#include "GCInterface.h"
#include "..\..\Intermediate\RootSet.generated.h"

namespace HopStep
{
	HCLASS();
	class HRootSet : public HObject
	{
		DECLARE_CLASS_BODY(HRootSet);

	public:

		~HRootSet();

		virtual bool IsGCRoot() const final { return true; }

		void AddToRoot(HObject* Object);

		virtual void GetGCProperties(TArray<IGCObject*>& OutList) override;

	protected:

		HPROPERTY();
		TArray<HObject*> Childs;
	};
}