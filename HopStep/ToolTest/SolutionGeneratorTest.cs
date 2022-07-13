using NUnit.Framework;
using SolutionGenerator;
using System;
using System.IO;
using System.Linq;

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
            {
                Assert.Fail();
                return;
            }

            _generator.SolutionRoot = _enginePath;
            _generator.Generate();

            var coreFilters = _generator.FilterSchema.Childs.FirstOrDefault(c => c.FilterName == "Core");
            Assert.IsNotNull(coreFilters);
            Assert.IsTrue(coreFilters?.FileNames.Exists(s => s == "CoreStandardIncludes.h"));
            Assert.IsTrue(coreFilters?.FileNames.Exists(s => s == "HopStepDefine.h"));
            Assert.IsTrue(coreFilters?.FileNames.Exists(s => s == "HopStepOverrides.h"));
            Assert.IsTrue(coreFilters?.FileNames.Exists(s => s == "PrimitiveTypeDefines.h"));

            var loggerFilter = coreFilters?.Childs.FirstOrDefault(f => f.FilterName == "Logger");
            Assert.IsNotNull(loggerFilter);
            Assert.IsTrue(loggerFilter?.FileNames.Exists(s => s == "ConsoleLogger.h"));
            Assert.IsTrue(loggerFilter?.FileNames.Exists(s => s == "LoggerBase.h"));
        }
    }
}
