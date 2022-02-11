cmake_minimum_required(VERSION 3.15)
project("OpenGL-project" LANGUAGES CXX)

# guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

SET(CMAKE_BUILD_TYPE Release)
SET(CMAKE_CXX_FLAGS_DISTRIBUTION "-O3")
SET(CMAKE_C_FLAGS_DISTRIBUTION "-O3")


set(main main)
set(gl_module gl_module)
set(gl_include ${CMAKE_CURRENT_SOURCE_DIR}/src/openGL_module)

file(GLOB subdirs "${CMAKE_CURRENT_SOURCE_DIR}/src/*")

foreach(dir ${subdirs})
    add_subdirectory(${dir})
endforeach()

