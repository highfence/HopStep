#pragma once
#include "..\..\Core\CoreExport.h"
#include "WeakObjectPtrImplement.h"
#include "Object.h"

namespace HopStep
{
	template <class TObjectType> requires std::derived_from<TObjectType, HObject>
	class TWeakObjectPtr
	{
	public:

		bool IsValid() const
		{
			return Internal::HWeakObjectPtrImplement::IsValid(ObjectIndex, ObjectSerialNumber);
		}

		TObjectType* Get() const
		{
			return static_cast<TObjectType*>(Internal::HWeakObjectPtrImplement::Get(ObjectIndex, ObjectSerialNumber));
		}

	private:


		uint32 ObjectIndex;
		uint32 ObjectSerialNumber;

		template <class TObjectType> requires std::derived_from<TObjectType, HObject>
		friend TWeakObjectPtr<TObjectType> MakeWeakObjectPtr(TObjectType* ObjectPtr);
	};

	template <class TObjectType> requires std::derived_from<TObjectType, HObject>
	TWeakObjectPtr<TObjectType> MakeWeakObjectPtr(TObjectType* ObjectPtr)
	{
		TWeakObjectPtr<TObjectType> WeakObjectPtr;

		WeakObjectPtr.ObjectIndex = ObjectPtr->GetGCPoolIndex();
		static std::atomic<uint32> PrimarySerialNumber = 0;

		WeakObjectPtr.ObjectSerialNumber = PrimarySerialNumber++;

		ObjectPtr->SetSerialNumber(WeakObjectPtr.ObjectSerialNumber);
		
		return WeakObjectPtr;
	}
}