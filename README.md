# About
Hamm Engine is a custom game engine made from scratch.
The Hamm Engine is made in C++ it uses OpenGL. Conan is used as a package manager for the project, and the project is built using CMake for cross-platform support.

# Getting Started
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