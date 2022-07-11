using System;
using System.Collections.Generic;

namespace HopStepHeaderTool
{
	using CommandParseFunc = Func<string, bool>;

	internal sealed class CommandParser
	{
		private List<CommandParseFunc> ParsingFunctions = new List<CommandParseFunc>();

		public void Parse(string[] args)
		{
			foreach (var arg in args)
			{
				ParsingFunctions.ForEach(f => f(arg));
			}
		}

		public CommandParseFunc GetParseFunc(string keyword, Action<string> resultAction)
		{
			return (string s) =>
			{
				if (s.Contains(keyword) == false) return false;

				var splitedCommand = s.Split(new string[] {keyword}, StringSplitOptions.None);
				if (splitedCommand.Length <= 1)
				{
					return false;
				}

				Console.WriteLine($"Found Command : {keyword}{splitedCommand[1]}");
				resultAction(splitedCommand[1]);

				return true;
			};
		}

		public void RegistParsingAction(CommandParseFunc func)
		{
			ParsingFunctions.Add(func);
		}
	}
}
