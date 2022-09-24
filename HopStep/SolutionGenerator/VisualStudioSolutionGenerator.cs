using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Xml;
using System.Xml.Linq;

namespace SolutionGenerator
{
    public class VisualStudioSolutionGenerator : ISolutionGenerator
    {
        public string SolutionRoot { get; private set; } = string.Empty;

        public string SolutionName => new DirectoryInfo(SolutionRoot).Name;

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

        public void Generate(string solutionRoot)
        {
            if (string.IsNullOrEmpty(solutionRoot)) return;

            SolutionRoot = solutionRoot;

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

            _flatFilterInfo.HeaderInclude.ForEach(headerInclude => 
            {
                var newNode = xmlDoc.CreateElement("ClInclude");
                newNode.SetAttribute("Include", headerInclude);
                headerGroup.AppendChild(newNode);
            });

            var cppGroup = itemGroupNodes[2];
            cppGroup.RemoveAll();

            _flatFilterInfo.CppInclude.ForEach(cppInclude => 
            {
                var newNode = xmlDoc.CreateElement("ClCompile");
                newNode.SetAttribute("Include", cppInclude);
                cppGroup.AppendChild(newNode);
            });

            if (File.Exists(projectFilePath))
            {
                File.Delete(projectFilePath);
            }

            xmlDoc.Save(projectFilePath);

            // Remove all 'xmlns' attribute except root
            XElement xmlElement = XElement.Parse(projectFilePath);
            var elementWithoutNs = RemoveAllNamesapces(xmlElement);
            elementWithoutNs.Save(projectFilePath);
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
            filterMetaGroup.RemoveAll();

            _flatFilterInfo.Filters.ForEach(filter => 
            {
                var newNode = xmlDoc.CreateElement("Filter");
                newNode.SetAttribute("Include", filter);
                filterMetaGroup.AppendChild(newNode);
                
                var guid = Guid.NewGuid().ToString();
                var newNode2 = xmlDoc.CreateElement("UniqueIdentifier");
                newNode2.InnerText = $"{{{guid}}}";
                newNode.AppendChild(newNode2);
            });

            XmlNode headerFilterGroup = itemGroupNodes[1];
            headerFilterGroup.RemoveAll();

            _flatFilterInfo.HeaderInclude.ForEach(headerPath => 
            {
                var newNode = xmlDoc.CreateElement("ClInclude");
                newNode.SetAttribute("Include", headerPath);

                var slashIndex = headerPath.LastIndexOf("\\");
                if (slashIndex != -1)
                {
                    var expectedFilterName = headerPath[..slashIndex];
                    var filterName = _flatFilterInfo.Filters.FirstOrDefault(f => f.Equals(expectedFilterName));

                    if (string.IsNullOrEmpty(filterName))
                    {
                        throw new Exception($"header : {expectedFilterName} is not exist!");
                    }

                    var newNode2 = xmlDoc.CreateElement("Filter");
                    newNode2.InnerText = filterName;
                    newNode.AppendChild(newNode2);
                }

                headerFilterGroup.AppendChild(newNode);
            });

            XmlNode cppFilterGroup = itemGroupNodes[2];
            cppFilterGroup.RemoveAll();

            _flatFilterInfo.CppInclude.ForEach(cppPath =>
            {
                var newNode = xmlDoc.CreateElement("ClCompile");
                newNode.SetAttribute("Include", cppPath);

                var slashIndex = cppPath.LastIndexOf("\\");
                if (slashIndex != -1)
                {
                    var expectedFilterName = cppPath[..slashIndex];
                    var filterName = _flatFilterInfo.Filters.FirstOrDefault(f => f.Equals(expectedFilterName));

                    if (string.IsNullOrEmpty(filterName))
                    {
                        throw new Exception($"cpp : {expectedFilterName} is not exist!");
                    }

                    var newNode2 = xmlDoc.CreateElement("Filter");
                    newNode2.InnerText = filterName;
                    newNode.AppendChild(newNode2);
                }

                cppFilterGroup.AppendChild(newNode);
            });

            xmlDoc.Save(projectFilePath);

            // Remove all 'xmlns' attribute except root
            XElement xmlElement = XElement.Parse(projectFilePath);
            var elementWithoutNs = RemoveAllNamesapces(xmlElement);
            elementWithoutNs.Save(projectFilePath);
        }
        private static XElement RemoveAllNamesapces(XElement xmlDocument)
        {
            if (!xmlDocument.HasElements)
            {
                XElement xElement = new XElement(xmlDocument.Name.LocalName);
                xElement.Value = xmlDocument.Value;

                foreach (XAttribute attribute in xmlDocument.Attributes())
                {
                    xElement.Add(attribute);
                }

                return xElement;
            }
            return new XElement(xmlDocument.Name.LocalName, xmlDocument.Elements().Select(el => RemoveAllNamesapces(el)));
        }
    }
}
