﻿using HopStepHeaderTool;
using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.IO;

namespace ToolTest
{
	internal class HeaderToolWriterTest
	{
		private HopStepGeneratedHeaderWriter? _writer;
		private string _enginePath = string.Empty;
        private string _intermediatePath = string.Empty;
        private SolutionSchema? _schema;

        [SetUp]
        public void Setup()
        {
            var currentDirectory = AppDomain.CurrentDomain.BaseDirectory;
            _enginePath = Path.Combine(currentDirectory, @"..\..\..\..\HopStepEngine\");
            _intermediatePath = Path.Combine(_enginePath, @"Intermediate_Test\");
            _writer = new HopStepGeneratedHeaderWriter();

            // schema setting
            _schema = new SolutionSchema();
            var objectHeaderPath = @$"{_enginePath}\\Object.h";
            _schema.HeaderDirectories.Add(objectHeaderPath);
            _schema.AddTypeInfo("HObject", SolutionSchema.ObjectType.Class, objectHeaderPath, new List<SolutionSchema.PropertyInfo>()
            {
                new SolutionSchema.PropertyInfo
                {
                    Name = "A",
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
                Directory.Delete(_intermediatePath, true);
			}
		}

        [Test]
        public void TestFilesExist()
		{
            _writer?.GenerateHeader(_intermediatePath, _schema);
            Assert.IsTrue(Directory.Exists(_intermediatePath));

            var targetFile = Path.Combine(_intermediatePath, "Object.generated.h");
            Assert.IsTrue(File.Exists(targetFile));

            string[] lines = File.ReadAllLines(targetFile);
            Int32 Index = 0;
            Assert.AreEqual(lines[Index++], "#pragma once");
            Assert.AreEqual(lines[Index++], "#include \"ObjectMacro.h\"");
            Assert.AreEqual(lines[Index++], "");
            Assert.AreEqual(lines[Index++], "void __Fill_Class_Property_HObject(HopStep::CoreObject::Reflection::HClass* InStaticClass)");
            Assert.AreEqual(lines[Index++], "{");
            Assert.AreEqual(lines[Index++], "   HStructBuilder::AddProperty<HObject, int32>(InStaticClass, \"a\", &HObject::a);");
            Assert.AreEqual(lines[Index++], "}");
		}
	}
}