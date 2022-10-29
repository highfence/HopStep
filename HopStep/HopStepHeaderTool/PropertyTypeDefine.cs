using System.Collections.Generic;

namespace HopStepHeaderTool
{
	internal class PropertyTypeDefine
	{
		private static Dictionary<string, string> _primitiveProperties = null;

		private static void InitializePrimitiveProperties()
		{
			if (_primitiveProperties != null) return;

			_primitiveProperties = new Dictionary<string, string>()
			{
				// NumericProperties
				{ "int8", "HNumericProperty" },
				{ "int16", "HNumericProperty" },
				{ "int32", "HNumericProperty" },
				{ "int64", "HNumericProperty" },
				{ "uint8", "HNumericProperty" },
				{ "uint16", "HNumericProperty" },
				{ "uint32", "HNumericProperty" },
				{ "uint64", "HNumericProperty" },

				// BooleanProperty
				{ "bool", "HBooleanProperty" },

				// CharacterProperty
				{ "HChar", "HCharacterProperty" },

				// StringProperty
				{ "HString", "HStringProperty" },

				// Container Property
				{ "HArray", "HArrayProperty" },
			};
		}
		
		public static string GetPropertyNameFromType(string propertyTypeName)
		{
			InitializePrimitiveProperties();

			propertyTypeName = propertyTypeName.TrimEnd('*');

			if (_primitiveProperties.ContainsKey(propertyTypeName))
			{
				return _primitiveProperties[propertyTypeName];
			}

			if (propertyTypeName.StartsWith('E'))
			{
				return "HEnumProperty";
			}

			return "HClassProperty";
		}
	}
}
