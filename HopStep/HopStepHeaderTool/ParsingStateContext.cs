using System.Collections.Generic;
using System.Text.RegularExpressions;

namespace HopStepHeaderTool
{
	public sealed class ParsingStateContext
	{
		public enum ParsingState
		{
			None,
			WaitForObjectName,
			WaitForObjectEnd,
			Done
		}

		public ParsingState State { get; private set; } = ParsingState.None;

        public SolutionSchema.ObjectType ObjectType = SolutionSchema.ObjectType.None;

		private Dictionary<string, SolutionSchema.ObjectType> _objectTypeDefines = new Dictionary<string, SolutionSchema.ObjectType>
		{
			{ "HOBJECT", SolutionSchema.ObjectType.Object },
			{ "HSTRUCT", SolutionSchema.ObjectType.Struct },
			{ "HPROPERTY", SolutionSchema.ObjectType.Property },
		};

        public bool ParseStringLine(string line)
        {
			if (State == ParsingState.None || State == ParsingState.Done)
            {
				var type = FindObjectTypeInString(line);
				if (type != SolutionSchema.ObjectType.None)
                {
					State = ParsingState.WaitForObjectName;
					ObjectType = type;
					return false;
                }
            }

			return false;
        }

		SolutionSchema.ObjectType FindObjectTypeInString(string line)
		{
			if (string.IsNullOrEmpty(line)) return SolutionSchema.ObjectType.None;

			foreach (var entry in _objectTypeDefines)
			{
				var regex = new Regex($"{entry.Key}\\(*\\)");

				if (regex.IsMatch(line))
				{
					return entry.Value;
				}
			}

			return SolutionSchema.ObjectType.None;
		}
	}
}
