using System.Collections.Generic;

namespace HopStepHeaderTool
{
    public class SolutionSchema
    {
        public enum ObjectType
        {
            None,
            Class,
            Struct,
            Property,
        }

        public class TypeInfo
        {
            public ObjectType Type = ObjectType.None;
            public string Name = string.Empty;
            public List<PropertyInfo> Fields = new List<PropertyInfo>();
        }

        public class PropertyInfo
        {
            public string Name = string.Empty;
            public string PropertyType = string.Empty;
        }

        public List<string> HeaderDirectories { get; internal set; } = new List<string>();

        public Dictionary<string, TypeInfo> Types = new Dictionary<string, TypeInfo>();

        public void AddTypeInfo(string name, ObjectType type, List<PropertyInfo> fields)
        {
            if (Types.ContainsKey(name))
            {
                throw new System.Exception($"Duplicated type name. name : {name}, type : {type}");
            }

            Types.Add(name, new TypeInfo
            {
                Type = type,
                Name = name, 
                Fields = fields
            });
        }
    }
}
