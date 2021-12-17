cmake_minimum_required(VERSION 3.2)

project(CFGConstruction)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")
set(CMAKE_BUILD_TYPE Debug)

find_package(Boost CONFIG REQUIRED program_options filesystem)

include_directories(CFG)
include_directories(opcodes)
include_directories(SolidityInfo)
include_directories(Utils)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(main main.cpp CFG/cfgbuilder/CfgBuilder.cpp CFG/SymbolicExecution/SymbolicExecutionStack.cpp Utils/Tools.h Utils/fifo_map.hpp)
target_link_libraries(main PUBLIC Boost::program_options Boost::filesystem)
