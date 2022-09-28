namespace HopStepHeaderTool
{
	public interface ISolutionContentGenerator
	{
		void GenerateContent(string enginePath, string intermediatePath, SolutionSchema solutionSchema);
	}
}
