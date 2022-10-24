using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace HopStepHeaderTool
{
    public class HopStepSolutionParser : ISolutionParser
    {
        public SolutionSchema SolutionSchema { get; private set; } = null;

        private string _modulePath = string.Empty;
        private readonly ParsingStateContext _parseContext = null;

        public HopStepSolutionParser()
        {
            _parseContext = new ParsingStateContext();
            SolutionSchema = new SolutionSchema();
        }

        public void Parse(string modulePath)
        {
            _modulePath = modulePath;
            TryFetchTargetFiles();
            ParseHeader();
        }

        public bool TryFetchTargetFiles()
        {
            try
            {
                var fullPath = Path.GetFullPath(_modulePath);
                var dirInfo = new DirectoryInfo(fullPath);
                var headerFiles = dirInfo.GetFiles("*.h", SearchOption.AllDirectories).Where(di => di.FullName.Contains("generated.") == false);

                foreach (var headerFile in headerFiles)
                {
                    SolutionSchema.HeaderDirectories.Add(headerFile.FullName);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex);
                return false;
            }

            return true;
        }

        public void ParseHeader()
        {
            foreach (var headerPath in SolutionSchema.HeaderDirectories)
            {
                var headerLines = File.ReadAllLines(headerPath);
                    //.Where(line => string.IsNullOrEmpty(line) == false);

                foreach (var line in headerLines)
                {
                    var isObjectEnd = _parseContext.ParseStringLine(line);

                    if (isObjectEnd)
                    {
                        SolutionSchema.AddTypeInfo(
                            _parseContext.TypeName,
                            _parseContext.CurrentObjectType,
                            headerPath,
                            _parseContext.DeclareLineNumber,
                            _parseContext.Properties,
                            _parseContext.ObjectBase,
                            _parseContext.Functions
                        );

                        _parseContext.SetObjectEnd();
                    }
                }

                _parseContext.SetFileEnd();
            }
        }
    }
}
