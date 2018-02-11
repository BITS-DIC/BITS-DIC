# Build Instructions

## Windows - tested on Windows 10
### Prerequisites
1. **Visual Studio** - Tested on Visual Studio 2017 (Community Edition)
2. **Qt** - Tested on Qt 5.10.0

- Open the `Native Tools Command Prompt for VS 2017` and execute following in it.

```sh
# Assuming Qt is installed at C:\Qt\Qt5.10.0
# and you are at root directory of project
c:\Qt\Qt5.10.0\5.10.0\msvc2017_64\bin\qmake.exe BITS-DIC.pro -o Makefile
nmake
C:\Qt\Qt5.10.0\5.10.0\msvc2017_64\bin\windeployqt.exe release\BITS-DIC.exe
```

This will create the software ready to deploy in `release` directory.

