# CMakeList.txt : CMake project for HammEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_compile_definitions(GAMEENGINE_EXPORTS)

# Include conan packages
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Add source to this project's executable.
file(GLOB_RECURSE source_list "*.cpp" "*.h")
add_library (HammEngine SHARED ${source_list})

set_target_properties(HammEngine PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin")
set_target_properties(HammEngine PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE  "${CMAKE_BINARY_DIR}/bin")
set_target_properties(HammEngine PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO   "${CMAKE_BINARY_DIR}/bin")
set_target_properties(HammEngine PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL   "${CMAKE_BINARY_DIR}/bin")

target_link_libraries(HammEngine ${CONAN_LIBS})

# TODO: Add tests and install targets if needed.
