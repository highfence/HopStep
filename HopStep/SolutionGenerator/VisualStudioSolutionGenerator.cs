using System;
using System.Collections.Generic;
using System.IO;
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

        public void Generate()
        {
            if (string.IsNullOrEmpty(SolutionRoot)) return;

            GatherSolutionFilter();

            ModifyProjectFile();
        }

        private void GatherSolutionFilter()
        {
            var gatherer = new DirectoryInfoGatherer(SolutionRoot);
            gatherer.Gather();

            FilterSchema = gatherer.RootSchema;
        }

        private void ModifyProjectFile()
        {
            var projectFilePath = System.IO.Path.Combine(SolutionRoot, $@"{SolutionName}.vcxproj");

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
                newNode.RemoveAttribute("xmlns");
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
                newNode.RemoveAttribute("xmlns");
            }

            foreach (var filter in schema.Childs)
            {
                var childDirectory = string.Concat(baseDirectory, filter.FilterName, "\\");
                AppendCppInfoRecursive(xmlDoc, xmlNode, filter, childDirectory);
            }
        }
    }
}
