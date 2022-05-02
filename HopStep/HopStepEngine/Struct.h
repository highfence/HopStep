#pragma once
#include "ReflectionConcepts.h"
#include "Type.h"

namespace HopStep::CoreObject::Reflection
{
	/**
	 */
	class HStruct : public HType
	{
	public:

		HStruct(const HString& InName) : HType(InName) 
		{
			RegisterToLibrary();
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
		const std::vector<class HProperty*> GetProperties(bool bIncludeSuper = true);


	private:

		/**
		 *
		 */
		HStruct* Super = nullptr;

		/**
		 *
		 */
		std::vector<class HProperty*> Properties;
	};
}
