using NUnit.Framework;
using System;
using System.IO;
using HopStepHeaderTool;

namespace ToolTest
{
    internal class HeaderToolParsetTest
    {
        private HopStepSolutionParser _parser = null;
        private string _enginePath = string.Empty;
        private string _intermediatePath = string.Empty;

        [SetUp]
        public void Setup()
        {
            var currentDirectory = AppDomain.CurrentDomain.BaseDirectory;
            _enginePath = Path.Combine(currentDirectory, @"..\..\..\..\HopStepEngine\");
            _intermediatePath = Path.Combine(_enginePath, @"Intermeditate\");
            _parser = new HopStepSolutionParser(_enginePath);
        }

        [TearDown]
        public void Teardown()
        {

        }

        [Test]
        public void TestParseHeader()
        {
            _parser.Parse();
            Assert.IsTrue(_parser.SolutionSchema.HeaderDirectories.Count > 0);

            foreach (var header in _parser.SolutionSchema.HeaderDirectories)
            {
                File.Exists(header);
            }

            var types = _parser.SolutionSchema.Types;
            Assert.IsTrue(types.Count > 0);
        }

        [Test]
        public void TestParsingContext()
        {
            var parseContext = new ParsingStateContext();
            Assert.IsTrue(parseContext.State == ParsingStateContext.ParsingState.None);

            Assert.IsFalse(parseContext.ParseStringLine("HOBJECT();"));
            Assert.AreEqual(parseContext.State, ParsingStateContext.ParsingState.WaitForObjectName);
            Assert.AreEqual(parseContext.ObjectType, SolutionSchema.ObjectType.Object);
        }
    }
}
