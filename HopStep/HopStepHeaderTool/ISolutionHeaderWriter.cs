using System;
using System.Collections.Generic;
using System.Text;

namespace HopStepHeaderTool
{
	public interface ISolutionHeaderWriter
	{
		void GenerateHeader(SolutionSchema solutionSchema);
	}
}
