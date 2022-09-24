start /B /WAIT %~dp0\HopStepHeaderTool\bin\Release\netcoreapp3.1\HopStepHeaderTool.exe Solution=%~dp0\HopStepEngine\ Intermediate=%~dp0\HopStepEngine\Intermediate\
start /B /WAIT %~dp0\SolutionGenerator\bin\Release\netcoreapp3.1\SolutionGenerator.exe %~dp0\HopStepEngine\
pause
