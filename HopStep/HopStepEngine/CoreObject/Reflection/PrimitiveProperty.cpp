#include "PrimitiveProperty.h"

namespace HopStep::CoreObject::Reflection
{
	// todo : Fix this
	void HNumericProperty::ExportToString(HString& TextOutput, void const* ObjectPtr) const
	{
		auto AppendValueString = [ObjectPtr, &TextOutput, this] <class TType> () -> void
		{
			TType* Value = this->GetPtr<TType>(ObjectPtr);
			TextOutput += std::to_wstring(*Value);
		};

		if (GetPropertyFlag(EPropertyFlag::FloatProperty))
		{
			// todo : check size is double
			AppendValueString.template operator()<float>();
		}
		else if (GetPropertyFlag(EPropertyFlag::IntProperty))
		{
			if (sizeof(int8) == ElementSize)
			{
				if (GetPropertyFlag(EPropertyFlag::UnsignedProperty))
				{
					AppendValueString.template operator()<uint8>();
				}
				else
				{
					AppendValueString.template operator()<int8>();
				}
			}
			else if (sizeof(int16) == ElementSize)
			{
				if (GetPropertyFlag(EPropertyFlag::UnsignedProperty))
				{
					AppendValueString.template operator()<uint16>();
				}
				else
				{
					AppendValueString.template operator()<int16>();
				}
			}
			else if (sizeof(int32) == ElementSize)
			{
				if (GetPropertyFlag(EPropertyFlag::UnsignedProperty))
				{
					AppendValueString.template operator()<uint32>();
				}
				else
				{
					AppendValueString.template operator()<int32>();
				}
			}
			else
			{
				if (GetPropertyFlag(EPropertyFlag::UnsignedProperty))
				{
					AppendValueString.template operator()<uint64>();
				}
				else
				{
					AppendValueString.template operator()<int64>();
				}
			}
		}
	}

	void HBooleanProperty::ExportToString(HString& TextOutput, void const* ObjectPtr) const
	{
		bool* Value = GetPtr<bool>(ObjectPtr);
		TextOutput += *Value ? L"true" : L"false";
	}

	void HCharacterProperty::ExportToString(HString& TextOutput, void const* ObjectPtr) const
	{
		HChar* Value = GetPtr<HChar>(ObjectPtr);
		TextOutput += *Value;
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

	void HArrayProperty::ExportToString(HString& TextOutput, void const* ObjectPtr) const
	{
	}
}
