using System.Collections.Generic;
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

				var objectName = RemoveFilePrefix(fileToken.Remove(fileToken.Length - 2));
				var generatedHeaderPath = Path.Combine(intermediatePath, $"{objectName}.generated.h");
				var schemasInHeader = solutionSchema.Types
					.Where(s => s.Value.HeaderDirectory == headerPath)
					.Select(s => s.Value).ToList();

				WriteHeader(generatedHeaderPath, schemasInHeader);

				var generatedCppPath = Path.Combine(intermediatePath, $"{objectName}.generated.cpp");
				WriteCpp(generatedCppPath, $"{objectName}.generated.h", schemasInHeader);
			}
		}

        private void WriteCpp(string generatedCppPath, string includeHeaderPath, List<SolutionSchema.TypeInfo> schemasInHeader)
        {
			using (var handle = new StreamWriter(generatedCppPath, false, Encoding.UTF8))
			{
				handle.WriteLine($"#include \"..\\HopStep.h\"");
				handle.WriteLine($"#include \"{includeHeaderPath}\"");

				foreach (var typeInfo in schemasInHeader)
                {
					var typeNameWithoutPrefix = RemoveFilePrefix(typeInfo.Name);
					handle.WriteLine($"#include \"..\\{typeNameWithoutPrefix}.h\"");
                }

				handle.WriteLine("");
				handle.WriteLine($"using namespace HopStep::CoreObject::Reflection;");

				foreach (var typeInfo in schemasInHeader)
				{
					handle.WriteLine("");
					handle.WriteLine($"void {typeInfo.Name}::__Fill_Class_Property_{typeInfo.Name}(HClass* InStaticClass)");
					handle.WriteLine("{");

					foreach (var propertyInfo in typeInfo.Fields)
					{
						handle.WriteLine($"\tHStructBuilder::AddProperty<{typeInfo.Name}, {propertyInfo.PropertyType}>(InStaticClass, TEXT(\"{propertyInfo.Name}\"), &{typeInfo.Name}::{propertyInfo.Name});");
					}
					handle.WriteLine("}");
					handle.WriteLine($"IMPLEMENT_CLASS({typeInfo.Name});");
				}

				// dispose
				handle.Close();
			}
        }

        private void WriteHeader(string generatedPath, List<SolutionSchema.TypeInfo> schemasInHeader)
		{
			using (var handle = new StreamWriter(generatedPath, false, Encoding.UTF8))
			{
				handle.WriteLine("#pragma once");
				handle.WriteLine("#include \"..\\ObjectMacro.h\"");
				handle.WriteLine("");
				// dispose
				handle.Close();
			}
		}

		private string RemoveFilePrefix(string fileDirectory)
        {
			if (string.IsNullOrEmpty(fileDirectory) || fileDirectory.StartsWith("H") == false) return fileDirectory;

			return fileDirectory.Substring(1);
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
