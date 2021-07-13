cmake_minimum_required(VERSION 3.0)

project(CfgConstruction)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")

set(CMAKE_BUILD_TYPE Debug)

include_directories(CFG)

include_directories(opcodes)

include_directories(SolidityInfo)

include_directories(Utils)

add_executable(main main.cpp CFG/cfgbuilder/CfgBuilder.cpp CFG/SymbolicExecution/SymbolicExecutionStack.cpp)
