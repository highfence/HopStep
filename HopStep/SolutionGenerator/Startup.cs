using System;

namespace SolutionGenerator
{
	internal class Startup
	{
		static void Main(string[] args)
		{
			Console.ForegroundColor = ConsoleColor.Cyan;
			Console.WriteLine("SolutionGenerator started...");

			if (args.Length == 0)
			{
				Console.Write("No Arguments!");
				return;
			}

			Console.WriteLine($"args : {string.Join(" ", args)}");

			var solutionRoot = args[0];

			ISolutionGenerator solutionGenerator = new VisualStudioSolutionGenerator();	
			solutionGenerator.Generate(solutionRoot);
		}
	}
}
