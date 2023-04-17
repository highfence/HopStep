using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;
using static HopStepHeaderTool.SolutionSchema;

namespace HopStepHeaderTool
{
    public sealed class ParsingStateContext
    {
        public enum ParsingState
        {
            None,
            WaitForObjectName,
            WaitForObjectEnd,
            WaitForProperty,
            WaitForFunction,
            Done
        }

        public ParsingState State { get; private set; } = ParsingState.None;
        public ObjectType CurrentObjectType = ObjectType.None;

        public string TypeName { get; private set; } = string.Empty;

        public List<PropertyInfo> Properties { get; internal set; } = new List<PropertyInfo>();

        public int BracketStack { get; private set; } = 0;

		public List<string> ObjectBase { get; private set; } = new List<string>();

        public List<FunctionInfo> Functions { get; private set; } = new List<FunctionInfo>();

        public int DeclareLineNumber { get; private set; } = -1;

        private readonly Dictionary<string, ObjectType> _objectTypeDefines = new Dictionary<string, ObjectType>
        {
            { "HCLASS", ObjectType.Class },
            { "HSTRUCT", ObjectType.Struct },
            { "HPROPERTY", ObjectType.Property },
            { "HFUNCTION", ObjectType.Function },
        };

        private bool _isInMultiLineAnnotation = false;
        private bool _isObjectStarted = false;
        private int _currentLine = 0;

        // Todo : FSM 형태로 변환?
        public bool ParseStringLine(string input)
        {
            _currentLine++;
            var line = FilteringAnnotationString(input);

            if (State == ParsingState.None || State == ParsingState.Done)
            {
                var type = FindObjectTypeInString(line);
                if (type != ObjectType.None)
                {
                    State = ParsingState.WaitForObjectName;
                    CurrentObjectType = type;
                    return false;
                }
            }
            else if (State == ParsingState.WaitForObjectName)
            {
                var className = FindClassName(line);
                var baseNames = FindBaseClassNames(line);

                if (string.IsNullOrEmpty(className))
                {
                    throw new Exception($"Invalid class name input : {line}");
                }

                TypeName = className;
                ObjectBase = baseNames;

                State = ParsingState.WaitForObjectEnd;
            }
            else if (State == ParsingState.WaitForObjectEnd)
            {
                UpdateBraketStack(line);
                UpdateDeclareClassBody(line);

                var objectType = FindObjectTypeInString(line);
                if (objectType == ObjectType.Property)
                {
                    State = ParsingState.WaitForProperty;
                }
                else if (objectType == ObjectType.Function)
                {
                    State = ParsingState.WaitForFunction;
                }
                else if (objectType != ObjectType.None)
                {
                    throw new Exception($"Invalid property line! : {line}");
                }
            }
            else if (State == ParsingState.WaitForProperty)
            {
                string pattern;
                int typeMatchIndex = 1;
                int nameMatchIndex = 2;

                if (line.StartsWith("TObjectPtr"))
                {
                    pattern = @"\w+<\s*(?:class\s+)?(\w+)\s*>\s+([a-zA-Z0-9_]+)";
                }
                else if (line.StartsWith("TArray"))
                {
					pattern = @"(TArray<\s*(?:class\s+)?(\w+(?:\s*\*{0,2})?)\s*>)\s+([a-zA-Z0-9_]+)";
                    nameMatchIndex = 3;
				}
                else
                {
                    pattern = @"(?:(?:class\s+)?(\w+(?:\s*\*{0,2})?))\s+([a-zA-Z0-9_]+)(?:\s*=\s*(.+?))?\s*;";
                }

                Match match = Regex.Match(line, pattern);
                if (match.Success == false)
                {
                    throw new Exception($"Invalid property token!: {line}");
                }

                string propertyType = match.Groups[typeMatchIndex].Value;
                string propertyName = match.Groups[nameMatchIndex].Value;

                State = ParsingState.WaitForObjectEnd;
                Properties.Add(new PropertyInfo { PropertyType = propertyType, Name = propertyName });
            }
            else if (State == ParsingState.WaitForFunction)
            {
                if (line.Contains("template"))
                {
                    throw new Exception($"Do not use template function for HFUNCTION : {line}");
                }

                var separator = new char[2] { '(', ')' };
                string[] functionSplit = line.Split(separator);

                if (functionSplit.Length < 2)
                {
                    throw new Exception($"Invalid UFUNCTION definition line! : {line}");
                }

                string funcNameAndReturn = functionSplit[0];
                if (funcNameAndReturn.Contains("virtual"))
                {
                    throw new Exception($"Do not use 'virtual' keyword for HFUNCTION. : {line}");
                }

                var paramInfos = new List<FunctionInfo.FunctionParam>();
                if (string.IsNullOrEmpty(functionSplit[1]) == false)
                {
                    var paramTokens = functionSplit[1].Split(',');

                    foreach (var paramToken in paramTokens)
                    {
                        string[] singleParam = paramToken.Trim().Split(' ');
                        if (singleParam.Length < 2)
                        {
                            throw new Exception($"Invalid single param string! : {paramToken}");
                        }

                        var paramName = singleParam[^1];
                        var paramType = String.Join(' ', singleParam.Take(singleParam.Length - 1));

                        paramInfos.Add(new FunctionInfo.FunctionParam()
                        {
                            ParamName = paramName,
                            ParamType = paramType
                        });
                    }
                }

                string[] funcNameAndReturnTokens = funcNameAndReturn.Split(' ');

                var funcInfo = new FunctionInfo
                {
                    // Last word before '(' character must be name of this function...
                    Name = funcNameAndReturnTokens[^1],
                    // And before that, it will be return type.
                    ReturnType = String.Join(' ', funcNameAndReturnTokens.Take(funcNameAndReturnTokens.Length - 1)),
                    Params = paramInfos
                };

                Functions.Add(funcInfo);

                State = ParsingState.WaitForObjectEnd;
            }

            return State == ParsingState.WaitForObjectEnd && BracketStack is 0 && _isObjectStarted;
        }

        private void UpdateDeclareClassBody(string line)
        {
            if (line.Contains("DECLARE_CLASS_BODY(") == false) return;

            if (DeclareLineNumber != -1)
            {
                throw new Exception($"Duplicated DECLARE_CLASS_BODY in one class. Find in line {DeclareLineNumber} and {_currentLine} : {line}");
            }

            DeclareLineNumber = _currentLine;
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
            if (string.IsNullOrEmpty(line))
            {
                return SolutionSchema.ObjectType.None;
            }

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

        public string FilteringAnnotationString(string line)
        {
            string tempLine = line;

            if (_isInMultiLineAnnotation == false && tempLine.Contains("/*"))
            {
                string[] lineSplit = tempLine.Split("/*");
                _isInMultiLineAnnotation = true;
                return lineSplit.Length > 0 ? lineSplit[0].Trim() : string.Empty;
            }
            else if (_isInMultiLineAnnotation && tempLine.Contains("*/"))
            {
                string[] lineSplit = tempLine.Split("*/");
                _isInMultiLineAnnotation = false;
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

        public string FindClassName(string line)
		{
            Regex regex = new Regex("(class |struct )([a-z|A-Z|0-9]+)(:|{|\\s|$)");
            Match match = regex.Match(line);

            if (match.Success == false)
            {
                return string.Empty;
            }

            return match.Groups[2].Value;
		}

        public List<string> FindBaseClassNames(string line)
		{
            Regex reg = new Regex(":(\\s)*([a-z|A-Z|0-9|\\s|,]+)");
            Match match = reg.Match(line);

            if (match.Success == false)
            {
                return null;
            }

            string baseStrings = match.Groups[2].Value;
            List<string> results = new List<string>();

            foreach (var token in baseStrings.Split(','))
			{
                var baseString = token.Replace("public", "").Replace("protected", "").Replace("private", "").Trim();
                results.Add(baseString);
			}

            // single inheritance only.
            if (results.Where(s => s.StartsWith("H")).Count() > 1)
			{
                throw new Exception($"Object must have only one inheritance start with 'H'. Please inherit with interface. input line : {line}");
			}

            return results;
		}

        public void SetFileEnd()
        {
            _currentLine = 0;
        }

        public void SetObjectEnd()
        {
            State = ParsingState.None;
            CurrentObjectType = SolutionSchema.ObjectType.None;
            TypeName = string.Empty;
            Properties.Clear();
            BracketStack = 0;
            DeclareLineNumber = -1;
            ObjectBase?.Clear();
            Functions?.Clear();
            _isInMultiLineAnnotation = false;
            _isObjectStarted = false;
        }
    }
}
