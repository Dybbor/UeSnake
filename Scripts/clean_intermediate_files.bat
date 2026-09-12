
@echo off
call "%~dp0config.bat"

pushd "%~dp0.."

for %%f in (%dirsToRemove%) do (
    if exist "%%f" rmdir /s /q "%%f"
)
for %%f in (%filesToRemove%) do (
    if exist "%%f" del /q "%%f"
)
popd
