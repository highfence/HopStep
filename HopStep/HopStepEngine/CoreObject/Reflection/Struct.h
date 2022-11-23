#pragma once
#include "ReflectionConcepts.h"
#include "Property.h"
#include "Type.h"

namespace HopStep
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
		const TArray<HProperty*> GetProperties(bool bIncludeSuper = true);

		/**
		 *
		 */
		const HProperty* FindProperty(const HString& PropertyName);

		/**
		 *
		 */
		bool IsChildOf(const HStruct* OtherClass) const;

	private:

		/**
		 *
		 */
		HStruct* Super = nullptr;

		/**
		 *
		 */
		TArray<HUniquePtr<HProperty>> Properties;

		friend struct HStructBuilder;
	};
}
