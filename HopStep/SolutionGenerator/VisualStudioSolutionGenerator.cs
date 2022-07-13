using System;
using System.Collections.Generic;
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
            public List<string> FileNames = new List<string>();
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
            var projectXML = new XmlDocument();
            projectXML.Load(projectFilePath);

            var itemGroups = projectXML.SelectNodes("/Project/ItemGroup");
            Console.WriteLine(itemGroups.Count);

            foreach (var item in itemGroups)
            {
                Console.WriteLine(item.ToString());
            }
        }
    }
}
