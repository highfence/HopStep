using System;
using System.IO;

namespace HopStepHeaderTool
{
	internal class HopStepSolutionParser : ISolutionParser
	{
		public SolutionSchema SolutionSchema => throw new System.NotImplementedException();
		public void Parse(string path)
		{
			try
            {
				var fullPath = Path.GetFullPath(path);
				Console.WriteLine($"Solution path : {fullPath}");

				var dirInfo = new DirectoryInfo(fullPath);
				var headerFiles = dirInfo.GetFiles("*.h");

				foreach (var headerFile in headerFiles)
                {
					Console.WriteLine(headerFile.FullName);
                }
            }
            catch
            {
				throw new NotImplementedException();
            }
		}
	}
}
