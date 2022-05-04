using System;
using System.IO;

namespace HopStepHeaderTool
{
	public class HopStepSolutionParser : ISolutionParser
	{
		public SolutionSchema SolutionSchema { get; private set; } = null;

		public void Parse(string path)
		{
			SolutionSchema = new SolutionSchema();

			try
            {
				var fullPath = Path.GetFullPath(path);
				Console.WriteLine($"Solution path : {fullPath}");

				var dirInfo = new DirectoryInfo(fullPath);
				var headerFiles = dirInfo.GetFiles("*.h");

				foreach (var headerFile in headerFiles)
                {
					Console.WriteLine(headerFile.FullName);
					SolutionSchema.HeaderDirectories.Add(headerFile.FullName);
                }
            }
            catch (Exception ex)
            {
				Console.WriteLine(ex);
				throw new InvalidDataException(path);
            }
		}
	}
}
