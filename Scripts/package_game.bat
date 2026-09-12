@echo off

call "%~dp0config.bat"

"%RunUATPath%" BuildCookRun ^
-project="%ProjectPath%" ^
-platform="%Platform%" ^
-clientconfig="%Configuration%" ^
-archivedirectory="%ArchivePath%" ^
-build -cook -package -stage -archive -pak -allmaps
