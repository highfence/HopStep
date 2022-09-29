using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace HopStepHeaderTool
{
    public class SolutionSchema
    {
        public string SolutionName = string.Empty;

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
            public string HeaderDirectory = string.Empty;
            public List<PropertyInfo> Fields = new List<PropertyInfo>();
        }

        public struct PropertyInfo
        {
            public string Name;
            public string PropertyType;
        }

        public List<string> HeaderDirectories { get; internal set; } = new List<string>();

        public Dictionary<string, TypeInfo> Types = new Dictionary<string, TypeInfo>();

        public void AddTypeInfo(string name, ObjectType type, string headerDirectory, List<PropertyInfo> fields)
        {
            if (Types.ContainsKey(name))
            {
                throw new System.Exception($"Duplicated type name. name : {name}, type : {type}");
            }

            var copiedFields = new PropertyInfo[fields.Count];
            fields.CopyTo(copiedFields);

            Types.Add(name, new TypeInfo
            {
                Type = type,
                Name = name,
                HeaderDirectory = headerDirectory,
                Fields = copiedFields.ToList()
            });
        }
    }
}
