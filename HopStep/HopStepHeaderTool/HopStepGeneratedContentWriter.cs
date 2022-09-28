using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace HopStepHeaderTool
{
    public static class GeneratedContentHelper
    {
		public static string RemovePrefix(string fileDirectory)
        {
			if (string.IsNullOrEmpty(fileDirectory) || fileDirectory.StartsWith("H") == false) return fileDirectory;
			return fileDirectory.Substring(1);
        }

		public static void ClearIntermediatePath(string intermediatePath)
		{
			if (Directory.Exists(intermediatePath))
			{
				Directory.Delete(intermediatePath, true);
			}

			Directory.CreateDirectory(intermediatePath);
		}
	}

    public class HopStepGeneratedContentWriter : ISolutionContentGenerator
	{
		private string _enginePath = string.Empty;
		private string _intermediatePath = string.Empty;

		public void GenerateContent(string enginePath, string intermediatePath, SolutionSchema solutionSchema)
		{
			_enginePath = enginePath.Replace("\\\\", "\\");
			_intermediatePath = intermediatePath.Replace("\\\\", "\\");

			GeneratedContentHelper.ClearIntermediatePath(intermediatePath);

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
			var sb = new StringBuilder();
			sb.AppendLine($"#include \"..\\HopStep.h\"");
			sb.AppendLine($"#include \"{includeHeaderPath}\"");

			foreach (var typeInfo in schemasInHeader)
			{
				var relativeDirectory = GetRelativeDirectory(_intermediatePath, typeInfo.HeaderDirectory);
				sb.AppendLine($"#include \"{relativeDirectory}\"");
			}

			sb.AppendLine();
			sb.AppendLine($"using namespace HopStep::CoreObject::Reflection;");

			foreach (var typeInfo in schemasInHeader)
			{
				sb.AppendLine();
				sb.AppendLine($"void {typeInfo.Name}::__Fill_Class_Property_{typeInfo.Name}(HClass* InStaticClass)");
				sb.AppendLine("{");

				foreach (var propertyInfo in typeInfo.Fields)
				{
					sb.AppendLine($"\tHStructBuilder::AddProperty<{typeInfo.Name}, {propertyInfo.PropertyType}>(InStaticClass, TEXT(\"{propertyInfo.Name}\"), &{typeInfo.Name}::{propertyInfo.Name});");
				}
				sb.AppendLine("}");
				sb.AppendLine($"IMPLEMENT_CLASS({typeInfo.Name});");
			}

			using (var handle = new StreamWriter(generatedCppPath, false, Encoding.UTF8))
			{
				handle.Write(sb.ToString());
				handle.Close();
			}
		}

		private string GetRelativeDirectory(string sourceDirectory, string destDirectory)
		{
			var path1 = new Uri(sourceDirectory);
			var path2 = new Uri(destDirectory);

			var diff = path1.MakeRelativeUri(path2);
			return diff.OriginalString;
		}

		private void WriteHeader(string generatedPath, List<SolutionSchema.TypeInfo> schemasInHeader)
		{
			var sb = new StringBuilder();

			sb.AppendLine("#pragma once");
			sb.AppendLine("#include \"..\\CoreObject\\Object\\ObjectMacro.h\"");
			sb.AppendLine();

			using (var handle = new StreamWriter(generatedPath, false, Encoding.UTF8))
			{
				handle.Write(sb.ToString());
				handle.Close();
			}
		}
	}
}
