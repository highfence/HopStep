﻿namespace HopStepHeaderTool
{
	internal class HopStepHeaderTool
	{
		private string _path;
		private readonly ISolutionParser _parser;

		public HopStepHeaderTool(string path)
		{
			_path = path;
			_parser = new HopStepSolutionParser(path);
		}

		public bool Process()
		{
			_parser?.Parse();
			return true;
		}
	}
}
