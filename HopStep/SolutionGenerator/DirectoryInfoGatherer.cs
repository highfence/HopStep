using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace SolutionGenerator
{
    internal sealed class DirectoryInfoGatherer
	{
        public readonly VisualStudioSolutionGenerator.SolutionFilterSchema RootSchema;
        private readonly DirectoryInfo _rootDirectory;

        public DirectoryInfoGatherer(string root)
		{
            _rootDirectory = new DirectoryInfo(root);
            RootSchema = new VisualStudioSolutionGenerator.SolutionFilterSchema();
		}

        public void Gather()
		{
            GatherRecursive(RootSchema, _rootDirectory);
		}

        private void GatherRecursive(VisualStudioSolutionGenerator.SolutionFilterSchema schema, DirectoryInfo directoryInfo)
		{
            schema.FilterName = directoryInfo.Name;

            void GatherFiles(string fileRegex, List<string> destList)
            {
                directoryInfo.GetFiles(fileRegex).ToList().ForEach(fi => destList.Add(fi.Name));
            }

            GatherFiles("*.h", schema.HeaderFileNames);
            GatherFiles("*.cpp", schema.CppFileNames);
            GatherFiles("*.vs", schema.ShaderFileNames);
            GatherFiles("*.ps", schema.ShaderFileNames);

            var subDirectories = directoryInfo.GetDirectories();
            foreach (var subDirectory in subDirectories)
			{
                if (subDirectory.Name.Contains("x64"))
				{
                    continue;
				}

                var subSchema = new VisualStudioSolutionGenerator.SolutionFilterSchema();
                GatherRecursive(subSchema, subDirectory);

                schema.Childs.Add(subSchema);
			}
		}
	}
}
