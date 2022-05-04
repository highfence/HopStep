namespace HopStepHeaderTool
{
	internal class HopStepHeaderTool
	{
		private string _path;
		private readonly ISolutionParser _parser;

		public HopStepHeaderTool(string path)
		{
			_path = path;
			_parser = new HopStepSolutionParser();
		}

		public bool Process()
		{
			_parser?.Parse(_path);
			return true;
		}
	}
}
