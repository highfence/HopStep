using System;

namespace HopStepHeaderTool
{
	public class StartUp
	{
		static void Main(string[] args)
		{
			var prevConsoleColor = Console.ForegroundColor;

			try
			{
				Console.ForegroundColor = ConsoleColor.Yellow;
				Console.WriteLine($"{nameof(HopStepHeaderTool)} started...");
				Console.WriteLine($"args : {string.Join(" ", args)}");

				var parser = new CommandParser();
				var config = new HeaderToolConfig();

				config.BindParsingArgs(parser);
				parser.Parse(args);

				var hopStepHeaderTool = new HopStepHeaderTool(config);
				hopStepHeaderTool.Process();
			}
			finally
			{
				Console.ForegroundColor = prevConsoleColor;
			}
		}
	}
}
