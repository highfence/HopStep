#include "PrimitiveProperty.h"

namespace HopStep::CoreObject::Reflection
{
	void HNumericProperty::ExportToString(HString& TextOutput, void const* ObjectPtr) const
	{
		if (GetPropertyFlag(EPropertyFlag::FloatProperty))
		{
			// check size is double

		}
		else if (GetPropertyFlag(EPropertyFlag::IntProperty))
		{
			// check size is uint8

			// check is unsigned
		}

	}

	void HBooleanProperty::ExportToString(HString& TextOutput, void const* ObjectPtr) const
	{
		bool Value = GetValue<bool>(ObjectPtr);
		TextOutput += Value ? L"true" : L"false";
	}

	void HCharacterProperty::ExportToString(HString& TextOutput, void const* ObjectPtr) const
	{

	}

	void HStringProperty::ExportToString(HString& TextOutput, void const* ObjectPtr) const
	{

	}

	void HEnumProperty::ExportToString(HString& TextOutput, void const* ObjectPtr) const
	{

	}

	void HClassProperty::ExportToString(HString& TextOutput, void const* ObjectPtr) const
	{

	}
}
