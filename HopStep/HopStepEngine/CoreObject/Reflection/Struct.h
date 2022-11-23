#pragma once
#include "ReflectionConcepts.h"
#include "Type.h"

namespace HopStep
{
	class HProperty;

	/**
	 * Manage inheritance & properties
	 */
	class HStruct : public HType
	{
	public:

		explicit HStruct(const HString& InName);

		/**
		 * Type can't not created by default or copy ctor.
		 * It must be unique.
		 */
		HStruct() = delete;
		HStruct(const HStruct&) = delete;

		virtual ~HStruct();

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

		template <StaticClassGetable TType>
		bool IsChildOf() const
		{
			const HStruct* OtherClass = TType::StaticClass();
			return IsChildOf(OtherClass);
		}


	private:

		/**
		 *
		 */
		HStruct* Super = nullptr;

		/**
		 *
		 */
		TArray<HUniquePtr<class HProperty>> Properties;

		friend struct HStructBuilder;
	};
}
