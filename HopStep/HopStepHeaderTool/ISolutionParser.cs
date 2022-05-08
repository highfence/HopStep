namespace HopStepHeaderTool
{
	internal interface ISolutionParser
	{
		void Parse();

		SolutionSchema SolutionSchema { get; }
	}
}
