using NUnit.Framework;
using System;
using System.IO;
using HopStepHeaderTool;

namespace ToolTest
{
    internal class HeaderToolParsetTest
    {
        private HopStepSolutionParser? _parser;
		private string _enginePath = string.Empty;
        private string _intermediatePath = string.Empty;

        [SetUp]
        public void Setup()
        {
            var currentDirectory = AppDomain.CurrentDomain.BaseDirectory;
            _enginePath = Path.Combine(currentDirectory, @"..\..\..\..\HopStepEngine\");
            _intermediatePath = Path.Combine(_enginePath, @"Intermediate\");
            _parser = new HopStepSolutionParser(_enginePath);
        }

        [TearDown]
        public void Teardown()
        {

        }

        [Test]
        public void TestParseHeader()
        {
            if (_parser == null)
			{
                Assert.Fail();
                return;
			}

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

            Assert.IsFalse(parseContext.ParseStringLine("HCLASS();"));
            Assert.AreEqual(parseContext.State, ParsingStateContext.ParsingState.WaitForObjectName);
            Assert.AreEqual(parseContext.ObjectType, SolutionSchema.ObjectType.Class);

            Assert.IsFalse(parseContext.ParseStringLine("class HObject"));
            Assert.AreEqual(parseContext.State, ParsingStateContext.ParsingState.WaitForObjectEnd);
            Assert.AreEqual(parseContext.TypeName, "HObject");


        }
    }
}
