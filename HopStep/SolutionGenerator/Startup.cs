using System;

namespace SolutionGenerator
{
	internal class Startup
	{
		static void Main(string[] args)
		{
			Console.Write("SolutionGenerator started...");

			if (args.Length == 0)
			{
				Console.Write("No Arguments!");
				return;
			}

			var solutionRoot = args[0];

			ISolutionGenerator solutionGenerator = new VisualStudioSolutionGenerator();	
			solutionGenerator.Generate(solutionRoot);
		}
	}
}
