using NUnit.Framework;
using SolutionGenerator;
using System;
using System.IO;

namespace ToolTest
{
    internal class SolutionGeneratorTest
    {
        private VisualStudioSolutionGenerator? _generator;
        private string _enginePath = string.Empty;

        [SetUp]
        public void Setup()
        {
            _generator = new VisualStudioSolutionGenerator();
            var currentDirectory = AppDomain.CurrentDomain.BaseDirectory;
            _enginePath = Path.Combine(currentDirectory, @"..\..\..\..\HopStepEngine\");
        }

        [Test]
        public void TestFileTree()
        {
            if (_generator is null)
                return;

            _generator.SolutionRoot = _enginePath;
            _generator.Generate();
        }
    }
}
