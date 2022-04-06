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
		template <class TDerivedType>
		HType(Internal::HTypeGenerator<TDerivedType>&& Generator)
			: Name(std::move(Generator.Name))
		{

		}

	private:

		void RegisterTypeMetaData();

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
