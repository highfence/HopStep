using System.IO;

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

            var currentDirectoryFiles = directoryInfo.GetFiles("*.h");
            foreach (var fileInfo in currentDirectoryFiles)
			{
                var fileName = fileInfo.Name;
                schema.FileNames.Add(fileName);
			}

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
