﻿using HopStepHeaderTool;
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
        private SolutionSchema? _schema;

        [SetUp]
        public void Setup()
        {
            var currentDirectory = AppDomain.CurrentDomain.BaseDirectory;
            _enginePath = Path.Combine(currentDirectory, @"..\..\..\..\HopStepEngine\");
            _intermediatePath = Path.Combine(_enginePath, @"Intermediate_Test\");
            _writer = new HopStepGeneratedContentWriter();

            // schema setting
            _schema = new SolutionSchema();
            var objectHeaderPath = @$"{_enginePath}\\HReflectionTest.h";
            _schema.HeaderDirectories.Add(objectHeaderPath);
            _schema.AddTypeInfo("HReflectionObjectTest", SolutionSchema.ObjectType.Class, objectHeaderPath, new List<SolutionSchema.PropertyInfo>()
            {
                new SolutionSchema.PropertyInfo
                {
                    Name = "A",
                    PropertyType = "int32"
                },

                new SolutionSchema.PropertyInfo
                {
                    Name = "B",
                    PropertyType = "int32"
                },

                new SolutionSchema.PropertyInfo
                {
                    Name = "C",
                    PropertyType = "int32"
                }
            });

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
				// Directory.Delete(_intermediatePath, true);
			}
		}

        [Test]
        public void TestFilesWellGenerated()
		{
            _writer?.GenerateContent(_intermediatePath, _schema);
            Assert.IsTrue(Directory.Exists(_intermediatePath));

            var targetHeaderFile = Path.Combine(_intermediatePath, "HReflectionObjectTest.generated.h");
            Assert.IsTrue(File.Exists(targetHeaderFile));

            var targetCppFile = Path.Combine(_intermediatePath, "HReflectionObjectTest.generated.cpp");
            Assert.IsTrue(File.Exists(targetCppFile));

            string[] lines = File.ReadAllLines(targetCppFile);
            Int32 Index = 0;
            Assert.AreEqual(lines[Index++], "#include \"..\\HopStep.h\"");
            Assert.AreEqual(lines[Index++], "#include \"..\\ReflectionTest.h\"");
            Assert.AreEqual(lines[Index++], "#include \"ReflectionTest.generated.h\"");
            Assert.AreEqual(lines[Index++], "");
            Assert.AreEqual(lines[Index++], "using namespace HopStep::CoreObject::Reflection;");
            Assert.AreEqual(lines[Index++], "");
            Assert.AreEqual(lines[Index++], "void HReflectionObjectTest::__Fill_Class_Property_HReflectionObjectTest(HClass* InStaticClass)");
            Assert.AreEqual(lines[Index++], "{");
            Assert.AreEqual(lines[Index++], "   HStructBuilder::AddProperty<HReflectionObjectTest, int32>(InStaticClass, \"A\", &HReflectionObjectTest::A);");
            Assert.AreEqual(lines[Index++], "   HStructBuilder::AddProperty<HReflectionObjectTest, int32>(InStaticClass, \"B\", &HReflectionObjectTest::B);");
            Assert.AreEqual(lines[Index++], "   HStructBuilder::AddProperty<HReflectionObjectTest, int32>(InStaticClass, \"C\", &HReflectionObjectTest::C);");
            Assert.AreEqual(lines[Index++], "}");
            Assert.AreEqual(lines[Index++], "IMPLEMENT_CLASS(HReflectionObjectTest);");
		}
	}
}
