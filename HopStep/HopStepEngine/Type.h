#pragma once
#include "ReflectionConcepts.h"
#include "TypeGenerator.h"

namespace HopStep::CoreObject::Reflection
{
	/**
	 *
	 */
	class HType
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
			: Name(std::move(Generator.Name))
			, Size(sizeof(TType))
		{
			RegisterToMetaData();
		}

		/**
		 *
		 */
		const std::wstring& GetName() const;

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
		std::wstring Name;

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
