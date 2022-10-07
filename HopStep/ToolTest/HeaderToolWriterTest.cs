using HopStepHeaderTool;
using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.IO;

namespace ToolTest
{
	internal class HeaderToolWriterTest
	{
		private HopStepGeneratedContentWriter? _writer;
		private string _enginePath = string.Empty;
        private string _intermediatePath = string.Empty;
        private string _solutionPath = string.Empty;
        private SolutionSchema? _schema;

        [SetUp]
        public void Setup()
        {
            var currentDirectory = AppDomain.CurrentDomain.BaseDirectory;
            _enginePath = Path.Combine(currentDirectory, @"..\..\..\..\HopStepEngine\");
            _solutionPath = Path.Combine(_enginePath, @"..\");
            _intermediatePath = Path.Combine(_enginePath, @"Intermediate_Test\");
            _writer = new HopStepGeneratedContentWriter();

            _schema = new SolutionSchema();

            if (Directory.Exists(_intermediatePath))
            {
                Directory.Delete(_intermediatePath, true);
            }
        }

        [TearDown]
        public void CleanUp()
		{
			if (Directory.Exists(_intermediatePath))
			{
				Directory.Delete(_intermediatePath, true);
			}
		}

        [Test]
        public void TestFilesWellGenerated()
		{
            // schema setting
            Assert.IsNotNull(_schema);
            var objectHeaderPath = @$"{_enginePath}ReflectionTest.h";
            _schema.HeaderDirectories.Add(objectHeaderPath);
            _schema.AddTypeInfo("HReflectionTest", SolutionSchema.ObjectType.Class, objectHeaderPath, new List<SolutionSchema.PropertyInfo>()
            {
                new SolutionSchema.PropertyInfo
                {
                    Name = "A",
                    PropertyType = "int32"
                },

                new SolutionSchema.PropertyInfo
                {
                    Name = "B",
                    PropertyType = "bool"
                },

                new SolutionSchema.PropertyInfo
                {
                    Name = "C",
                    PropertyType = "HObject"
                }
            });

            _writer?.GenerateContent(_enginePath, _intermediatePath, _schema);
            Assert.IsTrue(Directory.Exists(_intermediatePath));

            // check header file generated
            var targetHeaderFile = Path.Combine(_intermediatePath, "ReflectionTest.generated.h");
            Assert.IsTrue(File.Exists(targetHeaderFile), $"Header file doesn't exist! : {Path.GetFullPath(targetHeaderFile)}");
            {
                string[] headerLines = File.ReadAllLines(targetHeaderFile);
                var headerIndex = 0;
                Assert.AreEqual(headerLines[headerIndex++], "#pragma once");
                Assert.AreEqual(headerLines[headerIndex++], "#include \"..\\CoreObject\\Object\\ObjectMacro.h\"");
            }

            // check cpp file generated
            var targetCppFile = Path.Combine(_intermediatePath, "ReflectionTest.generated.cpp");
            Assert.IsTrue(File.Exists(targetCppFile));
            {
                string[] cppLines = File.ReadAllLines(targetCppFile);
                var cppIndex = 0;
                Assert.AreEqual(cppLines[cppIndex++], "#include \"HopStep.h\"");
                Assert.AreEqual(cppLines[cppIndex++], "#include \"ReflectionTest.generated.h\"");
                Assert.AreEqual(cppLines[cppIndex++], "#include \"ReflectionTest.h\"");
                Assert.AreEqual(cppLines[cppIndex++], "");
                Assert.AreEqual(cppLines[cppIndex++], "using namespace HopStep::CoreObject::Reflection;");
                Assert.AreEqual(cppLines[cppIndex++], "");
                Assert.AreEqual(cppLines[cppIndex++], "void HReflectionTest::__Fill_Class_Property_HReflectionTest(HClass* InStaticClass)");
                Assert.AreEqual(cppLines[cppIndex++], "{");
                Assert.AreEqual(cppLines[cppIndex++], "\tHStructBuilder::AddProperty<HReflectionTest, int32, HNumericProperty>(InStaticClass, TEXT(\"A\"), &HReflectionTest::A);");
                Assert.AreEqual(cppLines[cppIndex++], "\tHStructBuilder::AddProperty<HReflectionTest, bool, HBooleanProperty>(InStaticClass, TEXT(\"B\"), &HReflectionTest::B);");
                Assert.AreEqual(cppLines[cppIndex++], "\tHStructBuilder::AddProperty<HReflectionTest, HObject, HClassProperty>(InStaticClass, TEXT(\"C\"), &HReflectionTest::C);");
                Assert.AreEqual(cppLines[cppIndex++], "}");
                Assert.AreEqual(cppLines[cppIndex++], "IMPLEMENT_CLASS(HReflectionTest);");
            }
		}

        [Test]
        public void TestPointerProperty()
        {
            Assert.IsNotNull(_schema);
            var objectHeaderPath = @$"{_enginePath}ReflectionTest2.h";
            _schema.HeaderDirectories.Add(objectHeaderPath);
            _schema.AddTypeInfo("HReflectionTest2", SolutionSchema.ObjectType.Class, objectHeaderPath, new List<SolutionSchema.PropertyInfo>()
            {
                new SolutionSchema.PropertyInfo
                {
                    Name="Ptr",
                    PropertyType = "HObject*"
                }

            });

            _writer?.GenerateContent(_enginePath, _intermediatePath, _schema);
            Assert.IsTrue(Directory.Exists(_intermediatePath));

            var targetCppFile = Path.Combine(_intermediatePath, "ReflectionTest2.generated.cpp");
            Assert.IsTrue(File.Exists(targetCppFile));
            {
                string[] cppLines = File.ReadAllLines(targetCppFile);

                Console.WriteLine(cppLines);
            }
        }
	}
}
