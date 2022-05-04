namespace HopStepHeaderTool
{
	internal interface ISolutionParser
	{
		void Parse(string path);

		SolutionSchema SolutionSchema { get; }
	}
}
