# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("HammEngine")

set(CMAKE_CXX_STANDARD 17)

#if(EMSCRIPTEN)
#	add_compile_definitions(__EMSCRIPTEN__)
#	
#	set(EMSCRIPTEN_ROOT_PATH "$ENV{EMSCRIPTEN}")
#	include_directories("C:/Users/Michael/Desktop/emsdk/upstream/emscripten/system/lib/**")
#endif()

# Include sub-projects.
set(EXECUTABLE_OUTPUT_PATH "$C:/Users/Michael/source/repos/HammEngine/out/build/x64-debug/abc")

add_subdirectory ("HammEngine")
add_subdirectory ("ExampleGame")
