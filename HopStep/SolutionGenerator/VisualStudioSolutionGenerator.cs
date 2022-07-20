using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Xml;

namespace SolutionGenerator
{
	public class VisualStudioSolutionGenerator : ISolutionGenerator
    {
        public string SolutionRoot { get; set; } = string.Empty;

        public string SolutionName => new System.IO.DirectoryInfo(SolutionRoot).Name;

        // Solution filter must be correspond with directory folders
        public class SolutionFilterSchema
        {
            public string FilterName = string.Empty;
            public List<SolutionFilterSchema> Childs = new List<SolutionFilterSchema>();
            public List<string> HeaderFileNames = new List<string>();
            public List<string> CppFileNames = new List<string>();
        }

        public SolutionFilterSchema FilterSchema { get; set; }

        struct SolutionFilterInfo
		{
            public List<string> Filters;
            public List<string> HeaderInclude;
            public List<string> CppInclude;
		}

        private SolutionFilterInfo _flatFilterInfo;

        public void Generate()
        {
            if (string.IsNullOrEmpty(SolutionRoot)) return;

            GatherFilterSchemaInfo();

            _flatFilterInfo = new SolutionFilterInfo 
            {
                Filters = new List<string>(),
                HeaderInclude = new List<string>(),
                CppInclude = new List<string>()
            };

            MakeSolutionFilterInfo(FilterSchema, string.Empty);

            ModifyProjectFile();
            ModifyFilterFile();
        }

        private void GatherFilterSchemaInfo()
        {
            var gatherer = new DirectoryInfoGatherer(SolutionRoot);
            gatherer.Gather();

            FilterSchema = gatherer.RootSchema;
            FilterSchema.FilterName = string.Empty;
        }

        private void MakeSolutionFilterInfo(SolutionFilterSchema currentDirectorySchema, string previousDirectory)
		{
            var currentDirectory = Path.Combine(previousDirectory, currentDirectorySchema.FilterName);
            if (string.IsNullOrEmpty(currentDirectory) == false)
			{
                _flatFilterInfo.Filters.Add(currentDirectory);
                currentDirectory += "\\";
			}

            _flatFilterInfo.HeaderInclude.AddRange(currentDirectorySchema.HeaderFileNames.Select(headerName => $"{currentDirectory}{headerName}"));
            _flatFilterInfo.CppInclude.AddRange(currentDirectorySchema.CppFileNames.Select(cppName => $"{currentDirectory}{cppName}"));

            currentDirectorySchema.Childs.ForEach(child => MakeSolutionFilterInfo(child, currentDirectory));
		}

        private void ModifyProjectFile()
        {
            var projectFilePath = Path.Combine(SolutionRoot, $@"{SolutionName}.vcxproj");

            if (File.Exists(projectFilePath) == false)
            {
                throw new Exception($"Project file path {projectFilePath} doesn't exist!");
            }

            var xmlDoc = new XmlDocument();
            xmlDoc.Load(projectFilePath);

            XmlElement rootNode = xmlDoc.DocumentElement;
            if (rootNode == null)
            {
                throw new Exception("No document element!");
            }

            XmlNamespaceManager xmlNamespaceManager = new XmlNamespaceManager(xmlDoc.NameTable);
            xmlNamespaceManager.AddNamespace("t", "http://schemas.microsoft.com/developer/msbuild/2003");

            XmlNodeList itemGroupNodes = rootNode.SelectNodes("//t:ItemGroup", xmlNamespaceManager);
            if (itemGroupNodes.Count != 3)
            {
                throw new Exception("ItemGroup Node Count must be 3.");
            }

            var headerGroup  = itemGroupNodes[1];
            headerGroup.RemoveAll();
            AppendHeaderInfoRecursive(xmlDoc, headerGroup, FilterSchema, string.Empty);

            var cppGroup = itemGroupNodes[2];
            cppGroup.RemoveAll();
            AppendCppInfoRecursive(xmlDoc, cppGroup, FilterSchema, string.Empty);

            // Remove all 'xmlns' attribute except root
            foreach (XmlNode item in rootNode.ChildNodes)
            {
                var xmlnsAttribute = item.Attributes["xmlns"];
                item.Attributes.Remove(xmlnsAttribute);
            }

            xmlDoc.Save(projectFilePath);
        }

        private void AppendHeaderInfoRecursive(XmlDocument xmlDoc, XmlNode xmlNode, SolutionFilterSchema schema, string baseDirectory)
		{
            foreach (var fileName in schema.HeaderFileNames)
			{
                string fileNameWithDirectory = string.Concat(baseDirectory, fileName);
                Console.WriteLine($"Append header : {fileNameWithDirectory}");

                var newNode = xmlDoc.CreateElement("ClInclude");
                newNode.SetAttribute("Include", fileNameWithDirectory);
                xmlNode.AppendChild(newNode);
			}

            foreach (var filter in schema.Childs)
			{
                var childDirectory = string.Concat(baseDirectory, filter.FilterName, "\\");
                AppendHeaderInfoRecursive(xmlDoc, xmlNode, filter, childDirectory);
			}
		}

        private void AppendCppInfoRecursive(XmlDocument xmlDoc, XmlNode xmlNode, SolutionFilterSchema schema, string baseDirectory)
        {
            foreach (var fileName in schema.CppFileNames)
            {
                string fileNameWithDirectory = string.Concat(baseDirectory, fileName);
                Console.WriteLine($"Append cpp : {fileNameWithDirectory}");

                var newNode = xmlDoc.CreateElement("ClCompile");
                newNode.SetAttribute("Include", fileNameWithDirectory);
                xmlNode.AppendChild(newNode);
            }

            foreach (var filter in schema.Childs)
            {
                var childDirectory = string.Concat(baseDirectory, filter.FilterName, "\\");
                AppendCppInfoRecursive(xmlDoc, xmlNode, filter, childDirectory);
            }
        }

        private void ModifyFilterFile()
        {
            var projectFilePath = Path.Combine(SolutionRoot, $@"{SolutionName}.vcxproj.filters");

            if (File.Exists(projectFilePath) == false)
            {
                throw new Exception($"Project file path {projectFilePath} doesn't exist!");
            }

            var xmlDoc = new XmlDocument();
            xmlDoc.Load(projectFilePath);

            XmlElement rootNode = xmlDoc.DocumentElement;
            if (rootNode == null)
            {
                throw new Exception("No document element!");
            }

            XmlNamespaceManager xmlNamespaceManager = new XmlNamespaceManager(xmlDoc.NameTable);
            xmlNamespaceManager.AddNamespace("t", "http://schemas.microsoft.com/developer/msbuild/2003");

            XmlNodeList itemGroupNodes = rootNode.SelectNodes("//t:ItemGroup", xmlNamespaceManager);
            if (itemGroupNodes.Count != 3)
            {
                throw new Exception("ItemGroup Node Count must be 3.");
            }

            XmlNode filterMetaGroup = itemGroupNodes[0];  
        }

        private void AppendFilterMetaInfoRecursive(XmlDocument xmlDoc, XmlNode xmlNode, SolutionFilterSchema schema, string baseDirectory)
		{
            
		}
    }
}
