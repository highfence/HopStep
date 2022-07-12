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
}
