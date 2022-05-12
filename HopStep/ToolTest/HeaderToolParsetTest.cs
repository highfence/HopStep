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
            Assert.AreEqual(ParsingStateContext.ParsingState.WaitForObjectName, parseContext.State);
            Assert.AreEqual(SolutionSchema.ObjectType.Class, parseContext.ObjectType);

            Assert.IsFalse(parseContext.ParseStringLine("class HObject"));
            Assert.AreEqual(ParsingStateContext.ParsingState.WaitForObjectEnd, parseContext.State);
            Assert.AreEqual("HObject", parseContext.TypeName);

            Assert.AreEqual(0, parseContext.BracketStack);
            Assert.IsFalse(parseContext.ParseStringLine("{"));
            Assert.AreEqual(1, parseContext.BracketStack);

            Assert.IsFalse(parseContext.ParseStringLine("   HPROPERTY();"));
            Assert.AreEqual(ParsingStateContext.ParsingState.WaitForPropertyName, parseContext.State);

            Assert.IsFalse(parseContext.ParseStringLine("   int32 TestProperty;"));
            Assert.AreEqual(ParsingStateContext.ParsingState.WaitForObjectEnd, parseContext.State);
            Assert.IsTrue(parseContext.Properties.Count > 0);
            Assert.AreEqual("int32", parseContext.Properties[0].PropertyType);
            Assert.AreEqual("TestProperty", parseContext.Properties[0].Name);

            // Annotation test
            Assert.IsFalse(parseContext.ParseStringLine("// { is emtpy."));
            Assert.AreEqual(1, parseContext.BracketStack);
            Assert.IsFalse(parseContext.ParseStringLine("/*"));
            Assert.AreEqual(1, parseContext.BracketStack);
            Assert.IsFalse(parseContext.ParseStringLine("HPROPERTY();"));
            Assert.AreEqual(ParsingStateContext.ParsingState.WaitForObjectEnd, parseContext.State);
            Assert.IsFalse(parseContext.ParseStringLine("{"));
            Assert.AreEqual(1, parseContext.BracketStack);
            Assert.IsFalse(parseContext.ParseStringLine("}"));
            Assert.AreEqual(1, parseContext.BracketStack);
            Assert.IsFalse(parseContext.ParseStringLine("*/"));

            // Obejct end test
            Assert.AreEqual(1, parseContext.BracketStack);
            Assert.IsTrue(parseContext.ParseStringLine("}"));
            Assert.AreEqual(0, parseContext.BracketStack);
        }

        [Test]
        public void TestAnnotationTest()
        {
            var parseContext = new ParsingStateContext();

            // single line annotation
            Assert.AreEqual(parseContext.FilteringAnnotationString("class Test"), "class Test");
            Assert.AreEqual(parseContext.FilteringAnnotationString("// class Test"), string.Empty);
            Assert.AreEqual(parseContext.FilteringAnnotationString(" // class Test"), string.Empty);

            // multiline annotation
            Assert.AreEqual(parseContext.FilteringAnnotationString(" /*"), string.Empty);
            Assert.AreEqual(parseContext.FilteringAnnotationString("class MultiLineTest"), string.Empty);
            Assert.AreEqual(parseContext.FilteringAnnotationString("Test */"), string.Empty);
        }
    }
}
