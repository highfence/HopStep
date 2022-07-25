using System;

namespace SolutionGenerator
{
	internal class Startup
	{
		static void Main(string[] args)
		{
			if (args.Length == 0) return;

			var solutionRoot = args[0];

			ISolutionGenerator solutionGenerator = new VisualStudioSolutionGenerator();	
			solutionGenerator.Generate(solutionRoot);
		}
	}
}
