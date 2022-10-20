using NUnit.Framework;
using System;
using System.IO;
using HopStepHeaderTool;
using System.Linq;

namespace ToolTest
{
    internal class HeaderToolParserTest
    {
        private HopStepSolutionParser? _parser;
		private string _enginePath = string.Empty;

        [SetUp]
        public void Setup()
        {
            var currentDirectory = AppDomain.CurrentDomain.BaseDirectory;
            _enginePath = Path.Combine(currentDirectory, @"..\..\..\..\HopStepEngine\");
            _parser = new HopStepSolutionParser();
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

            _parser.Parse(_enginePath);
            Assert.IsTrue(_parser.SolutionSchema.HeaderDirectories.Count > 0);

            foreach (var header in _parser.SolutionSchema.HeaderDirectories)
            {
                File.Exists(header);
            }

            var types = _parser.SolutionSchema.Types;
            Assert.IsTrue(types.Count > 0);

            var reflectionTestType = types.FirstOrDefault(type => type.Key.Contains("ReflectionTest"));
            Assert.IsNotNull(reflectionTestType);
            Assert.IsNotEmpty(reflectionTestType.Value.Fields);
        }

        [Test]
        public void TestParsingContext()
        {
            var parseContext = new ParsingStateContext();
            Assert.IsTrue(parseContext.State == ParsingStateContext.ParsingState.None);

            Assert.IsFalse(parseContext.ParseStringLine("HCLASS();"));
            Assert.AreEqual(ParsingStateContext.ParsingState.WaitForObjectName, parseContext.State);
            Assert.AreEqual(SolutionSchema.ObjectType.Class, parseContext.CurrentObjectType);

            Assert.IsFalse(parseContext.ParseStringLine("class HObject"));
            Assert.AreEqual(ParsingStateContext.ParsingState.WaitForObjectEnd, parseContext.State);
            Assert.AreEqual("HObject", parseContext.TypeName);

            Assert.AreEqual(0, parseContext.BracketStack);
            Assert.IsFalse(parseContext.ParseStringLine("{"));
            Assert.AreEqual(1, parseContext.BracketStack);

            Assert.IsFalse(parseContext.ParseStringLine("   HPROPERTY();"));
            Assert.AreEqual(ParsingStateContext.ParsingState.WaitForProperty, parseContext.State);

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

        [Test]
        public void TestClassNameParse()
		{
            var parseContext = new ParsingStateContext();

            Assert.IsTrue(string.IsNullOrEmpty(parseContext.FindClassName("HCLASS();")));

            var className = parseContext.FindClassName("class HObject");
            Assert.AreEqual(className, "HObject");

            var inheritedClassName = parseContext.FindClassName("class HObject : public HBase");
            Assert.AreEqual(inheritedClassName, "HObject");

            var structName = parseContext.FindClassName("struct HStruct");
            Assert.AreEqual(structName, "HStruct");

            var inheritedStructName = parseContext.FindClassName("struct HStruct : public HBase");
            Assert.AreEqual(inheritedStructName, "HStruct");
		}

        [Test]
        public void TestBaseClassNameParse()
        {
            var parseContext = new ParsingStateContext();

            Assert.IsTrue(parseContext.FindBaseClassNames("") is null);
            Assert.IsTrue(parseContext.FindBaseClassNames("HCLASS();") is null);
            Assert.IsTrue(parseContext.FindBaseClassNames("class HObject") is null);

            var singleBaseResult = parseContext.FindBaseClassNames("class HObject : public HBase");
            Assert.IsNotNull(singleBaseResult);
            Assert.IsTrue(singleBaseResult.Count == 1);
            Assert.AreEqual("HBase", singleBaseResult[0]);

            // Wrong inheritance check.
            Assert.Throws<Exception>(() => parseContext.FindBaseClassNames("class HObject : public HBase1, private HBaseBase, protected HTestBase"));

            // Multiple inheritance check.
            var multipleBaseResult = parseContext.FindBaseClassNames("class HObject : public HBase1, public IBaseBase, public ITestBase");
            Assert.IsNotNull(multipleBaseResult);
            Assert.IsTrue(multipleBaseResult.Count == 3);
            Assert.IsTrue(multipleBaseResult.Exists(s => s == "HBase1"));
            Assert.IsTrue(multipleBaseResult.Exists(s => s == "IBaseBase"));
            Assert.IsTrue(multipleBaseResult.Exists(s => s == "ITestBase"));
        }

        [Test]
        public void TestFunctionParse()
        {
            var parseContext = new ParsingStateContext();

            parseContext.ParseStringLine("HCLASS();");
            parseContext.ParseStringLine("class HObject");
            parseContext.ParseStringLine("{");

            Assert.IsFalse(parseContext.ParseStringLine("HFUNCTION();"));
            Assert.AreEqual(ParsingStateContext.ParsingState.WaitForFunction, parseContext.State);

            Assert.IsFalse(parseContext.ParseStringLine("int32 Add(int32 a, int32 b);"));
            Assert.AreEqual(ParsingStateContext.ParsingState.WaitForObjectEnd, parseContext.State);
            Assert.IsTrue(parseContext.Functions.Exists(f => f.Name == "Add"));

            var AddFunction = parseContext.Functions.Find(f => f.Name == "Add");
            Assert.AreEqual("int32", AddFunction.ReturnType);

            Assert.AreEqual(2, AddFunction.Params.Count);
            Assert.IsTrue(AddFunction.Params.Exists(p => p.ParamName == "a" && p.ParamType == "int32"));
            Assert.IsTrue(AddFunction.Params.Exists(p => p.ParamName == "b" && p.ParamType == "int32"));


            Assert.IsFalse(parseContext.ParseStringLine("HFUNCTION();"));
            Assert.AreEqual(ParsingStateContext.ParsingState.WaitForFunction, parseContext.State);

            Assert.IsFalse(parseContext.ParseStringLine("void const* FindObject(HObject* InObject, const HString& ObjectName);"));
            Assert.AreEqual(ParsingStateContext.ParsingState.WaitForObjectEnd, parseContext.State);
            Assert.IsTrue(parseContext.Functions.Exists(f => f.Name == "FindObject"));

            var findObjectFunction = parseContext.Functions.Find(f => f.Name == "FindObject");
            Assert.AreEqual("void const*", findObjectFunction.ReturnType);
            Assert.AreEqual(2, findObjectFunction.Params.Count);
            Assert.IsTrue(findObjectFunction.Params.Exists(p => p.ParamName == "InObject" && p.ParamType == "HObject*"));
            Assert.IsTrue(findObjectFunction.Params.Exists(p => p.ParamName == "ObjectName" && p.ParamType == "const HString&"));
        }
    }
}
