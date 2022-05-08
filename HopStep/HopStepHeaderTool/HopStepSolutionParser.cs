﻿using System;
using System.IO;

namespace HopStepHeaderTool
{
    public partial class HopStepSolutionParser : ISolutionParser
	{
		public SolutionSchema SolutionSchema { get; private set; } = null;

		private string _modulePath = string.Empty;
		private ParsingStateContext _parseContext = null;

		public HopStepSolutionParser(string modulePath)
		{
			_modulePath = modulePath;
			_parseContext = new ParsingStateContext();
			SolutionSchema = new SolutionSchema();
		}

		public void Parse()
		{
			TryFetchTargetFiles();
			ParseHeader();
		}

		public bool TryFetchTargetFiles()
		{
			try
			{
				var fullPath = Path.GetFullPath(_modulePath);
				var dirInfo = new DirectoryInfo(fullPath);
				var headerFiles = dirInfo.GetFiles("*.h");

				foreach (var headerFile in headerFiles)
				{
					SolutionSchema.HeaderDirectories.Add(headerFile.FullName);
				}
			}
			catch (Exception ex)
			{
				Console.WriteLine(ex);
				return false;
			}

			return true;
		}

		public void ParseHeader()
		{
			foreach (var headerPath in SolutionSchema.HeaderDirectories)
			{
				var headerLines = File.ReadAllLines(headerPath);

				foreach (var line in headerLines)
				{

				}
			}
		}
	}
}
