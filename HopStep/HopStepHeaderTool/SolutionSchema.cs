﻿using System.Collections.Generic;
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
            Function,
        }

        public class TypeInfo
        {
            public ObjectType Type = ObjectType.None;
            public string Name = string.Empty;
            public string HeaderDirectory = string.Empty;
            public int DeclareLineNumber;
            public List<PropertyInfo> Fields = new List<PropertyInfo>();
            public List<string> BaseClasses = new List<string>();
            public List<FunctionInfo> Functions = new List<FunctionInfo>();
        }

        public struct PropertyInfo
        {
            public string Name;

            public string PropertyType;
        }

        public struct FunctionInfo
        {
            public struct FunctionParam
            {
                public string ParamName;
                public string ParamType;
            }

            public string Name;

            public string ReturnType;

            public List<FunctionParam> Params;
        }

        public List<string> HeaderDirectories { get; internal set; } = new List<string>();

        public Dictionary<string, TypeInfo> Types = new Dictionary<string, TypeInfo>();

        public void AddTypeInfo(
            string name
            , ObjectType type
            , string headerDirectory
            , int declareLineNumber
            , List<PropertyInfo> fields
            , List<string> baseClasses
            , List<FunctionInfo> functionInfos)
        {
            if (Types.ContainsKey(name))
            {
                throw new System.Exception($"Duplicated type name. name : {name}, type : {type}");
            }

            var copiedFields = new PropertyInfo[fields.Count];
            fields.CopyTo(copiedFields);

            var copiedBase = new List<string>();
            if (baseClasses != null && baseClasses.Count > 0)
            {
                var tempList = new string[baseClasses.Count];
                baseClasses?.CopyTo(tempList);
                copiedBase = tempList.ToList();
            }

            var copiedFunctions = new List<FunctionInfo>();
            if (functionInfos != null && functionInfos.Count > 0)
            {
                var tempList = new FunctionInfo[functionInfos.Count];
                functionInfos?.CopyTo(tempList);
                copiedFunctions = tempList.ToList();
            }

            Types.Add(name, new TypeInfo
            {
                Type = type,
                Name = name,
                HeaderDirectory = headerDirectory,
                DeclareLineNumber = declareLineNumber,
                Fields = copiedFields.ToList(),
                BaseClasses = copiedBase,
                Functions = copiedFunctions,
            });
        }
    }
}
