#pragma once
#include "ReflectionConcepts.h"
#include "Property.h"
#include "Type.h"

namespace HopStep::CoreObject::Reflection
{
	/**
	 * Manage inheritance & properties
	 */
	class HStruct : public HType
	{
	public:

		HStruct(const HString& InName) : HType(InName) 
		{
		};

		/**
		 * Type can't not created by default or copy ctor.
		 * It must be unique.
		 */
		HStruct() = delete;
		HStruct(const HStruct&) = delete;

		/**
		 *
		 */
		HStruct* GetSuper() const;

		/**
		 *
		 */
		const HArray<HProperty*> GetProperties(bool bIncludeSuper = true);

		/**
		 *
		 */
		const HProperty* FindProperty(const HString& PropertyName);

		/**
		 *
		 */
		template <class TValue, StaticClassGetable TInstanceType>
		TValue* GetPropertyPtr(TInstanceType* Instance, const HString& PropertyName);

		/**
		 *
		 */
		template <class TValue, StaticClassGetable TInstanceType>
		void ChangePropertyValue(TInstanceType* Instance, const HString& PropertyName, TValue Value);

	private:

		/**
		 *
		 */
		HStruct* Super = nullptr;

		/**
		 *
		 */
		HArray<HUniquePtr<HProperty>> Properties;

		friend struct HStructBuilder;
	};

	template<class TValue, StaticClassGetable TInstanceType>
	inline TValue* HStruct::GetPropertyPtr(TInstanceType* Instance, const HString& PropertyName)
	{
		HStruct* StaticClass = TInstanceType::StaticClass();
		if (StaticClass != this) return nullptr;

		const HProperty* FindingProperty = FindProperty(PropertyName);
		if (FindingProperty == nullptr) return nullptr;

		return FindingProperty->GetPtr<TValue>((void*)Instance);
	}

	template<class TValue, StaticClassGetable TInstanceType>
	inline void HStruct::ChangePropertyValue(TInstanceType* Instance, const HString& PropertyName, TValue Value)
	{
		const HProperty* Property = FindProperty(PropertyName);
		if (Property == nullptr) return;

		TValue* Ptr = Property->GetPtr<TValue>((void*)Instance);
		if (Ptr == nullptr) return;

		*Ptr = Value;
	}
}
