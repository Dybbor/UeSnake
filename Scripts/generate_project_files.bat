@echo off

call "%~dp0config.bat"

"%VersionSelector%" -switchversionsilent "%ProjectPath%" "%EnginePath%"