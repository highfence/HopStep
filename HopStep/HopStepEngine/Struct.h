#pragma once
#include "ReflectionConcepts.h"
#include "Field.h"

namespace HopStep::CoreObject::Reflection
{
	/**
	 */
	class HStruct : public HField
	{
	public:

		HStruct(const HString& InName) : HField(InName) 
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

		void RegisterToLibrary();

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
