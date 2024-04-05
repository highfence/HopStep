@echo off
set MS_BUILD="C:\Program Files\Microsoft Visual Studio\2022\Community\Msbuild\Current\Bin\MsBuild.exe"
set BAT_DIR=%~dp0
echo Current Batch Directory: %BAT_DIR%
echo MsBuild.exe: %MS_BUILD%

%MS_BUILD% /t:Rebuild /p:Configuration=Release %~dp0\HopStepHeaderTool\HopStepHeaderTool.csproj >nul 2>&1
%MS_BUILD% /t:Rebuild /p:Configuration=Release %~dp0\SolutionGenerator\SolutionGenerator.csproj >nul 2>&1

start /B /WAIT %~dp0HopStepHeaderTool\bin\Release\net8.0-windows10.0.22621.0\HopStepHeaderTool.exe Solution=%~dp0HopStepEngine\ Intermediate=%~dp0HopStepEngine\Intermediate\
start /B /WAIT %~dp0SolutionGenerator\bin\Release\net8.0-windows10.0.22621.0\SolutionGenerator.exe %~dp0HopStepEngine\
pause
