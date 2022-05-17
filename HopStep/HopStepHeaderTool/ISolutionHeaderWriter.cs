namespace HopStepHeaderTool
{
	public interface ISolutionHeaderWriter
	{
		void GenerateHeader(string intermediatePath, SolutionSchema solutionSchema);
	}
}
