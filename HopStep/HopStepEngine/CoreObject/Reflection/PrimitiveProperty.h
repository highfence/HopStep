#pragma once
#include "Enum.h"
#include "Property.h"
#include "..\Object\ObjectGlobals.h"

namespace HopStep
{
	class HNumericProperty : public HProperty
	{
	public:

		HNumericProperty(const HString& InName, int32 InOffset, int32 InElementSize, int32 InArrayDimension = 1)
			: HProperty(InName, InOffset, InElementSize, InArrayDimension)
		{
		}

		virtual ~HNumericProperty() {}

		virtual void ExportToString(HString& TextOutput, void const* ObjectPtr) const override;
	};

	class HBooleanProperty : public HProperty
	{
	public:

		HBooleanProperty(const HString& InName, int32 InOffset, int32 InElementSize, int32 InArrayDimension = 1)
			: HProperty(InName, InOffset, InElementSize, InArrayDimension)
		{
		}

		virtual ~HBooleanProperty() {}

		virtual void ExportToString(HString& TextOutput, void const* ObjectPtr) const override;
	};

	class HCharacterProperty : public HProperty
	{
	public:
		HCharacterProperty(const HString& InName, int32 InOffset, int32 InElementSize, int32 InArrayDimension = 1)
			: HProperty(InName, InOffset, InElementSize, InArrayDimension)
		{
		}

		virtual ~HCharacterProperty() {}

		virtual void ExportToString(HString& TextOutput, void const* ObjectPtr) const override;
	};

	class HStringProperty : public HProperty
	{
	public:
		HStringProperty(const HString& InName, int32 InOffset, int32 InElementSize, int32 InArrayDimension = 1)
			: HProperty(InName, InOffset, InElementSize, InArrayDimension)
		{
		}

		virtual ~HStringProperty() {}

		virtual void ExportToString(HString& TextOutput, void const* ObjectPtr) const override;
	};

	class HEnumProperty : public HProperty
	{
	public:

		HEnumProperty(const HString& InName, int32 InOffset, int32 InElementSize, int32 InArrayDimension = 1)
			: HProperty(InName, InOffset, InElementSize, InArrayDimension), Enum(nullptr)
		{
		}

		virtual ~HEnumProperty() {}

		HEnum* Enum;
		// HNumericProperty UnderlyingProperty;

		virtual void ExportToString(HString& TextOutput, void const* ObjectPtr) const override;
	};

	class HArrayProperty : public HProperty
	{
	public:

		HArrayProperty(const HString& InName, int32 InOffset, int32 InElementSize, int32 InArrayDimension = 1)
			: HProperty(InName, InOffset, InElementSize, InArrayDimension)
		{
		}

		virtual ~HArrayProperty() {}

		virtual void ExportToString(HString& TextOutput, void const* ObjectPtr) const override;
	};

	class HClassProperty : public HProperty
	{
	public:

		HClassProperty(const HString& InName, int32 InOffset, int32 InElementSize, int32 InArrayDimension = 1)
			: HProperty(InName, InOffset, InElementSize, InArrayDimension)
		{
		}

		virtual void ExportToString(HString& TextOutput, void const* ObjectPtr) const override;
	};

	class HObjectPtrProperty : public HProperty
	{
	public:

		HObjectPtrProperty(Internal::HPropertyParamBase& PropertyParam);

		virtual void ExportToString(HString& TextOutput, void const* ObjectPtr) const override;
	};
}

