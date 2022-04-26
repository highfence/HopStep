#pragma once
#include "Property.h"
#include "Enum.h"

namespace HopStep::CoreObject::Reflection
{
	class HNumericProperty : public HProperty
	{
	public:
	};

	class HBooleanProperty : public HProperty
	{
	public:
	};

	class HCharacterProperty : public HProperty
	{
	public:
	};

	class HStringProperty : public HProperty
	{
	public:
	};

	class HEnumProperty : public HProperty
	{
	public:

		HEnum* Enum;
		HNumericProperty UnderlyingProperty;
	};

	class HClassProperty : public HProperty
	{
	public:



	};
}

