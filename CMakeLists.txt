# outrun - ReXGlue Recompiled Project
#
# SDK boilerplate lives in generated/rexglue.cmake.

cmake_minimum_required(VERSION 3.25)
project(outrun LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(generated/rexglue.cmake)

# Sources
set(OUTRUN_SOURCES
    src/main.cpp
)

if(WIN32)
    add_executable(outrun WIN32 ${OUTRUN_SOURCES})
else()
    add_executable(outrun ${OUTRUN_SOURCES})
endif()

rexglue_setup_target(outrun)
