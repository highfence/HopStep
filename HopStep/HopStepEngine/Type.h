#pragma once
#include "ReflectionConcepts.h"
#include "TypeGenerator.h"

	/**
	 * 
	 */
class HType
{
	HType() = delete;
	HType(const HType&) = delete;

public:

	/**
	 *
	 */
	template <class TType> requires StaticClassGetable<TType>
	HType(HTypeGenerator<TType>&& Generator)
		: Name(std::move(Generator.Name)), Size(sizeof(TType))
	{
		RegisterTypeMetaData();
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
