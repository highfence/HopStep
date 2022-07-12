#pragma once
#include "Property.h"
#include "Enum.h"

namespace HopStep::CoreObject::Reflection
{
	class HNumericProperty : public HProperty
	{
	public:

		HNumericProperty(const HString& InName, int32 InOffset, int32 InElementSize, int32 InArrayDimension = 1)
			: HProperty(InName, InOffset, InElementSize, InArrayDimension)
		{
		}

		virtual ~HNumericProperty() {}
	};

	class HBooleanProperty : public HProperty
	{
	public:

		HBooleanProperty(const HString& InName, int32 InOffset, int32 InElementSize, int32 InArrayDimension = 1)
			: HProperty(InName, InOffset, InElementSize, InArrayDimension)
		{
		}

		virtual ~HBooleanProperty() {}
	};

	class HCharacterProperty : public HProperty
	{
	public:
		HCharacterProperty(const HString& InName, int32 InOffset, int32 InElementSize, int32 InArrayDimension = 1)
			: HProperty(InName, InOffset, InElementSize, InArrayDimension)
		{
		}

		virtual ~HCharacterProperty() {}
	};

	class HStringProperty : public HProperty
	{
	public:
		HStringProperty(const HString& InName, int32 InOffset, int32 InElementSize, int32 InArrayDimension = 1)
			: HProperty(InName, InOffset, InElementSize, InArrayDimension)
		{
		}

		virtual ~HStringProperty() {}
	};

	class HEnumProperty : public HProperty
	{
	public:

		virtual ~HEnumProperty() {}

		HEnum* Enum;
		HNumericProperty UnderlyingProperty;
	};

	class HClassProperty : public HProperty
	{
	public:



	};
}

