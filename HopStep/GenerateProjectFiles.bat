start /WAIT %~dp0\HopStepHeaderTool\bin\Release\netcoreapp3.1\HopStepHeaderTool.exe %~dp0\HopStepEngine\
start /WAIT %~dp0\SolutionGenerator\bin\Release\netcoreapp3.1\SolutionGenerator.exe %~dp0\HopStepEngine\
pause