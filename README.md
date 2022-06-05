*Getting Started
1) Download CMake
	https://cmake.org/download/
	Note: Make sure environment paths are setup
2) Download Conan
	https://docs.conan.io/en/latest/installation.html
	Note: Make sure environment paths are setup
3) mkdir out/build/x64-debug
4) cd out/build/x64-debug folder
5) Run 'conan install ../../.. --build=missing'
6) cd to root directory
7) Run 'cmake .'
8) Run 'cmake --build .'

WEBGL support:
1) Download emscripten
	https://emscripten.org/docs/getting_started/downloads.html#platform-notes-installation-instructions-sdk
	Note: When setting up make sure environment paths are setup: emsdk.bat activate --system
2) Download mingw if using windows https://sourceforge.net/projects/mingw/
