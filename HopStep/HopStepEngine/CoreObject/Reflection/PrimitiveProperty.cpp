#include "PrimitiveProperty.h"

namespace HopStep::CoreObject::Reflection
{
	void HNumericProperty::ExportToString(HString& TextOutput, void const* ObjectPtr) const
	{
		
	}

	void HBooleanProperty::ExportToString(HString& TextOutput, void const* ObjectPtr) const
	{
		bool Value = false;
		void* StartOffsetPtr = (void*)((char*)ObjectPtr + Offset);
		memcpy(&Value, StartOffsetPtr, ElementSize);
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
