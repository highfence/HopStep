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
		template <typename TValue, typename StaticClassGetable>
		TOptional<TValue> GetPropertyValue(StaticClassGetable* Instance, const HString& PropertyName);

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

	template<typename TValue, typename StaticClassGetable>
	inline TOptional<TValue> HStruct::GetPropertyValue(StaticClassGetable* Instance, const HString& PropertyName)
	{
		HStruct* StaticClass = StaticClassGetable::StaticClass();

		const HArray<HProperty*> Properties = StaticClass->GetProperties();
		auto FindingPropertyIter = std::find_if(Properties.begin(), Properties.end(), [PropertyName](const HProperty* InProperty) -> bool 
			{
				return InProperty->GetName() == PropertyName;
			});

		if (FindingPropertyIter == Properties.end()) return std::nullopt;

		const HProperty* FindingProperty = *FindingPropertyIter;
		void* StartOffsetPtr = (void*)((char*)Instance + FindingProperty->Offset);
		TValue Result;
		memcpy(&Result, StartOffsetPtr, FindingProperty->ElementSize);

		return TOptional<TValue>(Result);
	}
}
