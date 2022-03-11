#pragma once
#include "TypeGenerator.h"

namespace HopStep::Reflection
{
	/**
	 * 
	 */
	class HType
	{
		HType() = delete;
		HType(const HType&) = delete;

	public:

		template <class TType>
		HType()
			: Size(sizeof(TType))
		{

		}

		/**
		 * 
		 */
		const std::wstring& GetName() const;

		/**
		 * 
		 */
		size_t GetTypeHash() const;

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

		/**
		 * 
		 */
		template <class TType>
		HType(Internal::HTypeGenerator<TType>&& Generator)
			: Name(Generator.Name)
		{

		}

	private:

		/**
		 * 
		 */
		size_t TypeHash;

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
