namespace HopStepHeaderTool
{
    internal interface ISolutionParser
    {
        void Parse(string enginePath);

        SolutionSchema SolutionSchema { get; }
    }
}
