using System.Collections.Generic;

namespace HopStepHeaderTool
{
    public class SolutionSchema
    {
        public enum ObjectType
        {
            None,
            Object,
            Struct,
            Property,
        }

        public class TypeInfo
        {
            ObjectType Type = ObjectType.None;
            string Name = string.Empty;
            string Super = string.Empty;
        }

        public List<string> HeaderDirectories { get; internal set; } = new List<string>();

        public Dictionary<string, TypeInfo> Types = new Dictionary<string, TypeInfo>();

    }
}
