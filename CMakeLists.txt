cmake_minimum_required(VERSION 3.16)

project(swift)

set(CMAKE_CXX_STANDARD 17)

# LLVM >= 10.x.x
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(llvm_libs support core analysis irreader bitreader bitwriter coverage debuginfoDWARF
        profiledata instrumentation object objcarcopts mc mcparser
        bitreader bitwriter lto ipo option)

# SOURCE
include_directories(include)
add_subdirectory(lib)