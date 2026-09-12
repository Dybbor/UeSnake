@echo off

:: *************************** !! IMPORTANT !! ***************************
::
:: Required vars to set: EnginePath, ProjectPureName, VersionSelector
::
:: *************************** !! IMPORTANT !! ***************************

rem Unreal Engine params
set EnginePath=C:\Program Files\Epic Games\UE_5.8
set VersionSelector=C:\Program Files (x86)\Epic Games\Launcher\Engine\Binaries\Win64\UnrealVersionSelector.exe
set EditorPath=%EnginePath%\Engine\Binaries\Win64\UnrealEditor.exe
set RunUATPath=%EnginePath%\Engine\Build\BatchFiles\RunUAT.bat

rem Project params
set ProjectRoot=%~dp0..
set ProjectPureName=SnakeGame
set ProjectName=%ProjectPureName%.uproject
set ProjectPath=%ProjectRoot%\%ProjectName%
set SourceCodePath=%ProjectRoot%\Source

rem Build params
set Platform=Win64
:: Shipping, DebugGame
set Configuration=Development
set ArchivePath=%ProjectRoot%\Build

rem Other params
set dirsToRemove=Intermediate DerivedDataCache Saved Binaries .vs Build Documentation
set filesToRemove=*.sln

rem Target generation params
set EXTRA_MODULE_NAMES="%ProjectPureName%"
set TargetTemplateFilePath=%ProjectRoot%\devops_ue\targets\GameModule.Target.cs.template

rem Run
set ServerExePath=%ProjectRoot%\Build\WindowsServer\%ProjectPureName%Server.exe
set ClientExePath=%ProjectRoot%\Build\WindowsClient\%ProjectPureName%Client.exe
set GameExePath=%ProjectRoot%\Build\Windows\%ProjectPureName%.exe

rem Tests
set TestNames=
set TestOutputLogPath=%ProjectRoot%\Build\Tests\Tests.log
set ReportOutputPath=%ProjectRoot%\Build\Tests
set ExludedPathForTestReport=%SourceCodePath%\%ProjectPureName%\Tests
set UEAutomationContentPath=%EnginePath%\Engine\Content\Automation
set OpenCPPCoveragePath=C:\Program Files\OpenCppCoverage\OpenCppCoverage.exe