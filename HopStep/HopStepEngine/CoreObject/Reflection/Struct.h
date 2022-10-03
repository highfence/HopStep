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
		TOptional<TValue> GetPropertyValue(TInstanceType* Instance, const HString& PropertyName);

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
	inline TOptional<TValue> HStruct::GetPropertyValue(TInstanceType* Instance, const HString& PropertyName)
	{
		HStruct* StaticClass = TInstanceType::StaticClass();
		if (StaticClass != this) return std::nullopt;

		const HProperty* FindingProperty = FindProperty(PropertyName);

		void* StartOffsetPtr = (void*)((char*)Instance + FindingProperty->Offset);

		TValue Result;
		memcpy(&Result, StartOffsetPtr, FindingProperty->ElementSize);

		return TOptional<TValue>(Result);
	}

	template<class TValue, StaticClassGetable TInstanceType>
	inline void HStruct::ChangePropertyValue(TInstanceType* Instance, const HString& PropertyName, TValue Value)
	{
		const HProperty* Property = FindProperty(PropertyName);
		if (Property == nullptr) return;

		void* StartOffsetPtr = (void*)((char*)Instance + Property->Offset);
		memcpy(StartOffsetPtr, &Value, Property->ElementSize);
	}
}
