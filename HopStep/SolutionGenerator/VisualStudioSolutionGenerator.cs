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
            public List<string> ShaderFileNames = new List<string>();
        }

        public SolutionFilterSchema FilterSchema { get; set; }

        struct SolutionFilterInfo
		{
            public List<string> Filters;
            public List<string> HeaderInclude;
            public List<string> CppInclude;
            public List<string> ShaderInclude;
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
                CppInclude = new List<string>(),
                ShaderInclude = new List<string>(),
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
            _flatFilterInfo.ShaderInclude.AddRange(currentDirectorySchema.ShaderFileNames.Select(shaderName => $"{currentDirectory}{shaderName}"));

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
            xmlNamespaceManager.AddNamespace("t", "");

            XmlNodeList itemGroupNodes = rootNode.SelectNodes("//t:ItemGroup", xmlNamespaceManager);
            if (itemGroupNodes.Count != 4)
            {
                throw new Exception("ItemGroup Node Count must be 4.");
            }

            // todo : Instead doing RemoveAll(), compare and modify only changes.
            var headerGroup = itemGroupNodes[1];
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

                // todo : Implement for release configuration
                var complieConfigurationString = "'$(Configuration)|$(Platform)'=='Debug|x64'";

				// Add PrecompliedHeader file attributes
				var precompliedHeaderNode = xmlDoc.CreateElement("PrecompiledHeader");
                precompliedHeaderNode.SetAttribute("Condition", complieConfigurationString);
                precompliedHeaderNode.InnerText = "NotUsing";

                var precompliedHeaderFileNode = xmlDoc.CreateElement("PrecompiledHeaderFile");
                precompliedHeaderFileNode.SetAttribute("Condition", complieConfigurationString);

                cppGroup.AppendChild(newNode);
                newNode.AppendChild(precompliedHeaderNode);
                newNode.AppendChild(precompliedHeaderFileNode);
            });

            var otherGroup = itemGroupNodes[3];
            otherGroup.RemoveAll();

            _flatFilterInfo.ShaderInclude.ForEach(shaderInclude => 
            {
                var newNode = xmlDoc.CreateElement("None");
                newNode.SetAttribute("Include", shaderInclude);
                otherGroup.AppendChild(newNode);
            });

            if (File.Exists(projectFilePath))
            {
                File.Delete(projectFilePath);
            }

            var xmlRemovedDoc = RemoveAllEmptyNamespaces(xmlDoc);
            xmlRemovedDoc.Save(projectFilePath);
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
            xmlNamespaceManager.AddNamespace("t", "");

            XmlNodeList itemGroupNodes = rootNode.SelectNodes("//t:ItemGroup", xmlNamespaceManager);
            if (itemGroupNodes.Count != 4)
            {
                throw new Exception("ItemGroup Node Count must be 4.");
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

            XmlNode otherFilterGroup = itemGroupNodes[3];
            otherFilterGroup.RemoveAll();

            _flatFilterInfo.ShaderInclude.ForEach(shaderPath =>
            {
                var newNode = xmlDoc.CreateElement("None");
                newNode.SetAttribute("Include", shaderPath);

                var slashIndex = shaderPath.LastIndexOf("\\");
                if (slashIndex != -1)
                {
                    var expectedFilterName = shaderPath[..slashIndex];
                    var filterName = _flatFilterInfo.Filters.FirstOrDefault(f => f.Equals(expectedFilterName));

                    if (string.IsNullOrEmpty(filterName))
                    {
                        throw new Exception($"OtherFile : {expectedFilterName} is not exist!");
                    }

                    var newNode2 = xmlDoc.CreateElement("Filter");
                    newNode2.InnerText = filterName;
                    newNode.AppendChild(newNode2);
                }

                otherFilterGroup.AppendChild(newNode);
            });

            var xmlRemovedDoc = RemoveAllEmptyNamespaces(xmlDoc);
            xmlRemovedDoc.Save(projectFilePath);
        }

        private XmlDocument RemoveAllEmptyNamespaces(XmlDocument oldDocument)
        {
            XmlDocument newDom = new XmlDocument();
            newDom.LoadXml(System.Text.RegularExpressions.Regex.Replace(
                    oldDocument.OuterXml,
                    @"(xmlns:?[^=]*=[""][^""]*[""])",
                    "",
                    System.Text.RegularExpressions.RegexOptions.IgnoreCase |
                    System.Text.RegularExpressions.RegexOptions.Multiline
				));

            return newDom;
        }
    }
}
