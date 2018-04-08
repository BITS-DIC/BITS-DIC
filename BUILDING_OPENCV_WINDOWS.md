## Build Instructions for OpenCV

These instructions are for building OpenCV for use by the BITS-DIC application and QT, on a Windows PC using MinGW. It has been tested on Windows 10 64bit computer but should work on a modern Windows PC.

### Required downloads 

1. `OpenCV 3.2` from https://opencv.org/releases.html
2. `CMake 3.11.0 (cmake-gui)` from https://cmake.org/download/ 
3. `MinGW-w64` from https://mingw-w64.org/doku.php/download

## Installation
 
### MinGW-w64
Run `mingw-w64-install.exe` file. When the options load, choose the latest version (`7.3.0` as of this date),  `x86_64`  and `posix`. It is important to choose *posix* otherwise build failure occurs when building OpenCV. Rest of the options can be left as they are. You may require *7z* archive utility to be installed for decompression of downloaded setup (download [here](https://www.7-zip.org/download.html)). After installation is successful, you can run *Start > Run terminal* to verify.

#### PATH variable
After verification of MinGW-w64, we need to add the *bin* directory to the system environment PATH variable. E.g. *C:\Program Files\mingw-w64\x86_64-7.3.0-posix-seh-rt_v5-rev0\mingw64\bin*

### CMake
CMake installation is quite straightforward. When asked select *Add CMake to system PATH for all users*. This adds CMake *bin* directory to the system PATH variable.

### OpenCV
Extract the contents of the setup file to *C:\OpenCV\OpenCV3.2\*. Run CMake from Start menu.

Where is the source code *C:/OpenCV/OpenCV3.2/sources* 
Where to build the binaries *C:/OpenCV/OpenCV3.2/release*

Press *Configure*
Select *MinGW Makefiles* and *Use default compilers*

When the list loads, make the following changes

*Release* - *CMAKE_BUILD_TYPE*
✓ *ENABLE_SOLUTION_FOLDERS*
✓ *WITH_OPENGL*
✓ *WITH_QT (optional)*

Press *Configure*
For the new variables select the appropriate QT directories and press *Generate*.

Open *Run terminal* app of MinGW and cd into the *build* folder.

*C:\OpenCV\OpenCV3.2\release\ >* *mingw32-make*
*C:\OpenCV\OpenCV3.2\release\ >* *mingw32-make install*

Add the install binaries to system path variable. E.g. for x86 
*C:\OpenCV\OpenCV3.2\release\install\x86\mingw\bin*
Use the bin directory in QT like
```qt
INCLUDEPATH  +=  C:\OpenCV\OpenCV3.2\build\include

LIBS  +=  -LC:\OpenCV\OpenCV3.2\release\install\x86\mingw\lib  \
  -lopencv_core320  \
  -lopencv_highgui320

LIBS  +=  C:\OpenCV\OpenCV3.2\release\install\x86\mingw\bin\libopencv_core320.dll
LIBS  +=  C:\OpenCV\OpenCV3.2\release\install\x86\mingw\bin\libopencv_highgui320.dll
LIBS  +=  C:\OpenCV\OpenCV3.2\release\install\x86\mingw\bin\libopencv_imgcodecs320.dll
LIBS  +=  C:\OpenCV\OpenCV3.2\release\install\x86\mingw\bin\libopencv_imgproc320.dll
LIBS  +=  C:\OpenCV\OpenCV3.2\release\install\x86\mingw\bin\libopencv_features2d320.dll
LIBS  +=  C:\OpenCV\OpenCV3.2\release\install\x86\mingw\bin\libopencv_calib3d320.dll
```
