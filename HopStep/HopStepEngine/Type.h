#pragma once
#include "ReflectionConcepts.h"
#include "TypeGenerator.h"
#include "Field.h"

namespace HopStep::CoreObject::Reflection
{
	/**
	 *
	 */
	class HType : public HField
	{
	public:

		/**
		 * Type can't not created by default or copy ctor.
		 * It must be unique.
		 */
		HType() = delete;
		HType(const HType&) = delete;

		/**
		 *
		 */
		template <class TType> requires StaticClassGetable<TType>
		HType(HTypeGenerator<TType>&& Generator)
			: HField(Generator.Name)
			, Size(sizeof(TType))
		{
			RegisterToMetaData();
		}

		/**
		 *
		 */
		size_t GetSize() const;

		/**
		 *
		 */
		HType* GetSuper() const;

		/**
		 *
		 */
		const std::vector<class HProperty*> GetProperties(bool bIncludeSuper = true);


	private:

		void RegisterToMetaData();

		/**
		 *
		 */
		size_t Size;

		/**
		 *
		 */
		HType* Super = nullptr;

		/**
		 *
		 */
		std::vector<class HProperty*> Properties;
	};
}
