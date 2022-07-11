using System;

namespace HopStepHeaderTool
{
	public class StartUp
	{
		static string _solutionPath = string.Empty;

		static void Main(string[] args)
		{
			var parser = new CommandParser();
			var config = new HeaderToolConfig();

			config.BindParsingArgs(parser);
			parser.Parse(args);

			var hopStepHeaderTool = new HopStepHeaderTool(config);
			hopStepHeaderTool.Process();
		}
	}
}
