using System;
using System.Collections.Generic;
using System.Linq;
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
			WaitForPropertyName,
			Done
		}

		public ParsingState State { get; private set; } = ParsingState.None;
        public SolutionSchema.ObjectType ObjectType = SolutionSchema.ObjectType.None;
        public string TypeName { get; private set; } = string.Empty;
        public List<SolutionSchema.PropertyInfo> Properties { get; internal set; } = new List<SolutionSchema.PropertyInfo>();

		public int BracketStack { get; private set; } = 0;

        private Dictionary<string, SolutionSchema.ObjectType> _objectTypeDefines = new Dictionary<string, SolutionSchema.ObjectType>
		{
			{ "HCLASS", SolutionSchema.ObjectType.Class },
			{ "HSTRUCT", SolutionSchema.ObjectType.Struct },
			{ "HPROPERTY", SolutionSchema.ObjectType.Property },
		};

		private bool _isInMultiLineAnnotation = false;
		private bool _isObjectStarted = false;

        public bool ParseStringLine(string input)
        {
			var line = FilteringAnnotationString(input);

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
			else if (State == ParsingState.WaitForObjectName)
			{
				string[] tokens = line.Split(' ');

				var findClassDeclare = false;

				foreach (string token in tokens)
				{
					if (findClassDeclare)
					{
						TypeName = token;
						break;
					}

					if (token == "class" || token == "struct")
					{
						findClassDeclare = true;
					}
				}

				State = ParsingState.WaitForObjectEnd;
			}
			else if (State == ParsingState.WaitForObjectEnd)
            {
				UpdateBraketStack(line);

				var objectType = FindObjectTypeInString(line);
				if (objectType == SolutionSchema.ObjectType.Property)
                {
					State = ParsingState.WaitForPropertyName;
                }
				else if (objectType != SolutionSchema.ObjectType.None)
                {
					throw new Exception($"Invalid property line! : {line}");
                }
            }
			else if (State == ParsingState.WaitForPropertyName)
            {
				string[] tokens = line.Split(' ');
				string[] propertyToken = tokens.Where(s => string.IsNullOrEmpty(s) == false).Select(s => s.Trim(';')).ToArray();
				
				if (propertyToken.Length < 2)
                {
					throw new Exception($"Invalid property token! : {line}");
                }
				
				State = ParsingState.WaitForObjectEnd;
				Properties.Add(new SolutionSchema.PropertyInfo { PropertyType = propertyToken[0], Name = propertyToken[1] });
            }

			return State == ParsingState.WaitForObjectEnd && BracketStack is 0 && _isObjectStarted;
        }

		private void UpdateBraketStack(string line)
		{
			int openBracket = line.Count(c => c == '{');
			int closeBracket = line.Count(c => c == '}');

			if (openBracket > 0 && _isObjectStarted == false)
            {
				_isObjectStarted = true;
            }

			BracketStack += openBracket - closeBracket;
		}

		private SolutionSchema.ObjectType FindObjectTypeInString(string line)
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

        public void Reset()
        {
			State = ParsingState.None;
			ObjectType = SolutionSchema.ObjectType.None;
			TypeName = string.Empty;
			Properties.Clear();
			BracketStack = 0;
			_isInMultiLineAnnotation = false;
			_isObjectStarted = false;
        }

		public string FilteringAnnotationString(string line)
        {
			string tempLine = line;

			if (_isInMultiLineAnnotation == false && tempLine.Contains("/*"))
            {
				string[] lineSplit = tempLine.Split("/*");
				_isInMultiLineAnnotation = true;
				return lineSplit.Length > 0 ? lineSplit[0].Trim() : string.Empty;
            }
			else if(_isInMultiLineAnnotation && tempLine.Contains("*/"))
            {
				string[] lineSplit = tempLine.Split("*/");
				_isInMultiLineAnnotation= false;
				return lineSplit.Length > 1 ? lineSplit[1].Trim() : string.Empty;
            }
			else if (_isInMultiLineAnnotation)
            {
				return string.Empty;
            }

			string[] lineString = tempLine.Split("//");

			if (lineString.Length == 0)
            {
				return string.Empty;
            }

			return lineString[0].Trim();
        }
    }
}
