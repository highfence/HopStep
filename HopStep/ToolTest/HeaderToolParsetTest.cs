using NUnit.Framework;

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
            parser.Parse("../HopStepEngine/");
        }
    }
}
