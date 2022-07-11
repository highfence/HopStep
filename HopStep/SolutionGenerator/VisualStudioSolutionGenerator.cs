using System;
using System.Collections.Generic;
using System.IO;

namespace SolutionGenerator
{
    public class VisualStudioSolutionGenerator : ISolutionGenerator
    {
        public string SolutionRoot { get; set; } = string.Empty;

        public class SolutionFilterSchema
        {
            public string FilterName = string.Empty;
            public List<SolutionFilterSchema> Childs = new List<SolutionFilterSchema>();
        }

        public List<SolutionFilterSchema> FilterSchemas { get; set; } = new List<SolutionFilterSchema>();

        public void Generate()
        {
            if (string.IsNullOrEmpty(SolutionRoot)) return;

            var rootDirectory = new DirectoryInfo(SolutionRoot);

        }
    }
}
