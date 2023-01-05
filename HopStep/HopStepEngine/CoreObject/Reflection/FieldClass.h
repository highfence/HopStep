#pragma once
#include "..\..\Core\CoreExport.h"
#include "..\Object\NameTypes.h"

namespace HopStep
{
	class HFieldClass
	{
		HName Name;

		uint64 Id;

		uint64 CastFlags;

		HFieldClass* SuperClass;

		class HField* DefaultObject;

		class HField* (*ConstructFn)(const HName&);

		class HField* ConstructDefaultObject();

	public:

		explicit HFieldClass(const HChar* InName, uint64 InId, uint64 InCastFlags, HFieldClass* InSuperClass, class HField* (*ConstructFnPtr)(const HName&));
		~HFieldClass();

		static TArray<HFieldClass*>& GetAllFieldClasses();

		static TMap<HName, HFieldClass*>& GetNameFieldClassMap();

		inline HString GetName() const 
		{
			return Name.ToString();
		}

		inline HName GetHName() const
		{
			return Name;
		}

		inline uint64 GetID() const
		{
			return Id;
		}

		inline uint64 GetCastFlags() const
		{
			return CastFlags;
		}

		class HField* Construct(const HName& InName) const
		{
			return ConstructFn(InName);
		}

		HFieldClass* GetSuperClass() const
		{
			return SuperClass;
		}

		class HField* GetDefaultObject()
		{
			if (DefaultObject == nullptr)
			{
				DefaultObject = ConstructDefaultObject();
				HCheck(DefaultObject);
			}
			return DefaultObject;
		}
	};
}