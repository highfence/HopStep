using NUnit.Framework;
using System;
using System.IO;

namespace ToolTest
{
    internal class HeaderToolParsetTest
    {
        [SetUp]
        public void Setup()
        {

        }

        [TearDown]
        public void Teardown()
        {

        }

        [Test]
        public void ParseHeader()
        {
            var parser = new HopStepHeaderTool.HopStepSolutionParser();
            var currentDirectory = AppDomain.CurrentDomain.BaseDirectory;
            var enginePath = Path.Combine(currentDirectory, @"..\..\..\..\HopStepEngine\");
            parser.Parse(enginePath);
        }
    }
}
