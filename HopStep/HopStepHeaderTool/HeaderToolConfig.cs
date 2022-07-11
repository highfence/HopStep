using System;
using System.Collections.Generic;
using System.Text;

namespace HopStepHeaderTool
{
	internal class HeaderToolConfig
	{
		public string EnginePath { get; private set; } = string.Empty;
		public string IntermediatePath { get; private set; } = string.Empty;

		public void BindParsingArgs(CommandParser parser)
		{
			parser.RegistParsingAction(parser.GetParseFunc("Solution=", (string s) => { EnginePath = s; }));
			parser.RegistParsingAction(parser.GetParseFunc("Intermediate=", (string s) => { IntermediatePath = s; }));
		}
	}
}
