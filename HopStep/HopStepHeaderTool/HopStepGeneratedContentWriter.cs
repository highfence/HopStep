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

				if (schemasInHeader.Count == 0)
				{
					continue;
				}

				WriteHeader(generatedHeaderPath, headerPath, schemasInHeader);

				var generatedCppPath = Path.Combine(intermediatePath, $"{objectName}.generated.cpp");
				WriteCpp(generatedCppPath, $"{objectName}.generated.h", schemasInHeader);
			}
		}

		private void WriteCpp(string generatedCppPath, string includeHeaderPath, List<SolutionSchema.TypeInfo> schemasInHeader)
		{
			var sb = new StringBuilder();
			sb.AppendLine($"#include \"HopStep.h\"");
			sb.AppendLine($"#include \"{includeHeaderPath}\"");

			HashSet<string> includes = new HashSet<string>();

			foreach (var typeInfo in schemasInHeader)
			{
				var enginePath = Path.GetFullPath(_enginePath);
				var relativeDirectory = GetRelativeDirectory(enginePath, typeInfo.HeaderDirectory).Replace("/", "\\");

				if (includes.Contains(relativeDirectory)) continue;

				includes.Add(relativeDirectory);
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
					var propertyString = PropertyTypeDefine.GetPropertyNameFromType(propertyInfo.PropertyType);
					sb.AppendLine($"\tHStructBuilder::AddProperty<{typeInfo.Name}, {propertyInfo.PropertyType}, {propertyString}>" +
						$"(InStaticClass, TEXT(\"{propertyInfo.Name}\"), &{typeInfo.Name}::{propertyInfo.Name});");
				}

				var representiveBaseClassName = typeInfo.BaseClasses?.FirstOrDefault(s => s.StartsWith("H"));
				if (string.IsNullOrEmpty(representiveBaseClassName) == false)
				{
					sb.AppendLine($"\tHStructBuilder::SetSuper<{representiveBaseClassName}>(InStaticClass);");
				}

				if (typeInfo.Functions != null)
				{
					foreach (var f in typeInfo.Functions)
					{
						sb.AppendLine($"\tHStructBuilder::AddNativeFunction((HClass*)InStaticClass, &{typeInfo.Name}::exec{f.Name}, TEXT(\"{f.Name}\"));");
					}
				}

				sb.AppendLine("}");
				sb.AppendLine("");

				if (typeInfo.Functions != null)
				{
					foreach (var funcInfo in typeInfo.Functions)
					{
						sb.AppendLine($"DEFINE_FUNCTION({typeInfo.Name}::exec{funcInfo.Name})");
						sb.AppendLine("{");

						if (funcInfo.Params != null)
						{
							for (var paramIndex = funcInfo.Params.Count - 1; paramIndex >= 0; paramIndex--)
							{
								var paramInfo = funcInfo.Params[paramIndex];

								sb.AppendLine($"\t{PropertyFromFrameDefine}({paramInfo.ParamType}, {FunctionParamPrefix}{paramInfo.ParamName});");
							}
						}

						var paramString = funcInfo.Params == null ? string.Empty : string.Join(", ", funcInfo.Params.Select(param => $"{FunctionParamPrefix}{param.ParamName}"));

						sb.AppendLine($"\t*{FunctionResultParamDefine} = (void*){FunctionThisPtrDefine}->{funcInfo.Name}({paramString});");
						sb.AppendLine("}");
					}
					
					sb.AppendLine("");
				}

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

		private void WriteHeader(string generatedPath, string originHeaderPath, List<SolutionSchema.TypeInfo> schemasInHeader)
		{
			var sb = new StringBuilder();

			sb.AppendLine("#pragma once");
			sb.AppendLine("#include \"..\\CoreObject\\Object\\ObjectMacro.h\"");
			sb.AppendLine("#include \"..\\CoreObject\\Reflection\\ReflectionMacro.h\"");
			sb.AppendLine("#include \"..\\CoreObject\\Reflection\\Function.h\"");
			sb.AppendLine("");

			foreach (var typeInfo in schemasInHeader)
			{
				sb.AppendLine($"#define {GetGeneratedFunctionDeclareDefineId(originHeaderPath, typeInfo.DeclareLineNumber)} \\");

				if (typeInfo.Functions is null) continue;

				sb.AppendLine("public: \\");

				foreach (var funcInfo in typeInfo.Functions)
				{
					sb.AppendLine($"\tDECLARE_FUNCTION(exec{funcInfo.Name}); \\");
				}

				sb.AppendLine("private:");
			}

			sb.AppendLine("");
			sb.AppendLine("#undef CURRENT_FILE_ID");
			sb.AppendLine($"#define CURRENT_FILE_ID {GetCurrentFileId(originHeaderPath)}");

			using (var handle = new StreamWriter(generatedPath, false, Encoding.UTF8))
			{
				handle.Write(sb.ToString());
				handle.Close();
			}
		}

		public string GetGeneratedFunctionDeclareDefineId(string originHeaderPath, int declareLine)
		{
			return $"{GetCurrentFileId(originHeaderPath)}_{declareLine}_Generated_Function_Declare";
		}

		public string GetCurrentFileId(string originHeaderPath)
		{
			var basePath = System.IO.Directory.GetParent(_enginePath);
			var relativePath = GetRelativeDirectory(basePath.FullName, originHeaderPath);
			// SkipLast for removing ".h"
			relativePath = relativePath.Remove(relativePath.Length - 2, 2);
			return String.Join("_", relativePath.Split('/'));
		}

		public string FunctionParamPrefix => "HFunc_Param_";
		public string PropertyFromFrameDefine => "HFUNC_GET_FROM_FRAME";
		public string FunctionResultParamDefine => "HFUNC_RESULT_PARAM";
		public string FunctionThisPtrDefine => "HFUNC_THIS";
	}
}
