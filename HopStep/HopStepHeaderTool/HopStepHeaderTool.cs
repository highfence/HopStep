namespace HopStepHeaderTool
{
    internal class HopStepHeaderTool
    {
        private readonly HeaderToolConfig _config;
        private readonly ISolutionParser _parser;
        private readonly ISolutionContentGenerator _writer;

        public HopStepHeaderTool(HeaderToolConfig Config)
        {
            _config = Config;

            _parser = new HopStepSolutionParser();
            _writer = new HopStepGeneratedContentWriter();
        }

        public bool Process()
        {
            _parser?.Parse(_config.EnginePath);
            _writer?.GenerateContent(_config.EnginePath, _config.IntermediatePath, _parser.SolutionSchema);

            return true;
        }
    }
}
