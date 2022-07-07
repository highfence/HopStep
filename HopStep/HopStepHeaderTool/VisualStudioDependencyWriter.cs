using System.IO;

namespace HopStepHeaderTool
{
    public class VisualStudioDependencyWriter : ISolutionDependencyModifier
    {
        public string VCXExtension => ".vcxproj";
        public string VCXFilterExtension => ".vcxproj.filters";

        public void InjectFileDependency(string solutionRootPath, SolutionSchema solutionSchema)
        {
        }

        public bool IsTargetVCSFileExist(string solutionRootPath, string solutionName)
        {
            var targetFile = @$"{solutionName}\{solutionName}";
            var absSolutionRootPath = Path.GetFullPath(solutionRootPath);
            var vscFilePath = Path.Combine(absSolutionRootPath, $@"{targetFile}{VCXExtension}");

            if (File.Exists(vscFilePath) == false) return false;

            var vcsFilterFilePath = Path.Combine(absSolutionRootPath, $@"{targetFile}{VCXFilterExtension}");

            if (File.Exists(vcsFilterFilePath) == false) return false;

            return true;
        }
    }
}
