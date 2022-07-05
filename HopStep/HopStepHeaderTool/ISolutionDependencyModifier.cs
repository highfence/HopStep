using System;
using System.Collections.Generic;
using System.Text;

namespace HopStepHeaderTool
{
    internal interface ISolutionDependencyModifier
    {
        public void InjectFileDependency(string solutionRootPath, SolutionSchema solutionSchema);
    }
}
