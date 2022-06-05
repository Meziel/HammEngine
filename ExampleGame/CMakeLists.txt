# CMakeList.txt : CMake project for HammEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Include conan packages
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories("../HammEngine")

# Add source to this project's executable.
add_executable (ExampleGame "ExampleGame.cpp" "Player.cpp" "Cube.cpp")

set_target_properties(ExampleGame PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin")
set_target_properties(ExampleGame PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE  "${CMAKE_BINARY_DIR}/bin")
set_target_properties(ExampleGame PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO   "${CMAKE_BINARY_DIR}/bin")
set_target_properties(ExampleGame PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL   "${CMAKE_BINARY_DIR}/bin")

target_link_directories(ExampleGame PRIVATE "${CMAKE_BINARY_DIR}/HammeEngine/lib/")
target_link_libraries(ExampleGame HammEngine)
