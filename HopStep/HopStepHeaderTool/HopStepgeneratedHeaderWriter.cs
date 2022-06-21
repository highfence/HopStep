using System.IO;
using System.Linq;
using System.Text;

namespace HopStepHeaderTool
{
	public class HopStepGeneratedHeaderWriter : ISolutionHeaderWriter
	{
		public void GenerateHeader(string intermediatePath, SolutionSchema solutionSchema)
		{
			ClearIntermediatePath(intermediatePath);
			MakeFiles(intermediatePath, solutionSchema);
		} 

		public void MakeFiles(string intermediatePath, SolutionSchema solutionSchema)
		{
			foreach (var headerPath in solutionSchema.HeaderDirectories)
			{
				var fileToken = headerPath.Split("\\").LastOrDefault();
				if (string.IsNullOrEmpty(fileToken))
				{
					throw new System.Exception($"Invalid header path! can't find file token from : {headerPath}");
				}

				if (fileToken.EndsWith(".h") == false)
				{
					throw new System.Exception($"Invalid header path! header must end with \".h\" : {headerPath}");
				}

				var objectName = fileToken.Remove(fileToken.Length - 2);
				var generatedPath = Path.Combine(intermediatePath, $"{objectName}.generated.h");
				using (var handle = new StreamWriter(generatedPath, false, Encoding.UTF8))
				{
					handle.WriteLine("#pragma once");
					handle.WriteLine("#include \"ObjectMacro.h\"");

					// dispose
					handle.Close();
				}
			}
		}

		private void ClearIntermediatePath(string intermediatePath)
		{
			if (Directory.Exists(intermediatePath))
			{
				Directory.Delete(intermediatePath, true);
			}

			Directory.CreateDirectory(intermediatePath);
		}
	}
}
