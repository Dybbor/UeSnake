@echo off
setlocal

call "%~dp0config.bat"

set "Platform=Linux"
set "LinuxToolchainRoot=C:\UnrealToolchains\v26_clang-20.1.8-rockylinux8"

if not exist "%LinuxToolchainRoot%\x86_64-unknown-linux-gnu\bin\clang++.exe" (
    echo Linux toolchain was not found.
    echo Expected location:
    echo C:\UnrealToolchains\v26_clang-20.1.8-rockylinux8
    exit /b 1
)

set "LINUX_MULTIARCH_ROOT=%LinuxToolchainRoot%"

"%RunUATPath%" BuildCookRun ^
-project="%ProjectPath%" ^
-platform="%Platform%" ^
-clientconfig="%Configuration%" ^
-archivedirectory="%ArchivePath%" ^
-build -cook -package -stage -archive -pak -allmaps -nodebuginfo

exit /b %ERRORLEVEL%
