cmake_minimum_required(VERSION 3.28)
project(cpp_jni_implementation
        DESCRIPTION "C++ implementation of JNI interface"
)

if (MSVC)
    add_compile_options(/W4 /WX)
else ()
    message(using another compiler)
endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_STANDARD LESS 20)
    message(FATAL_ERROR "At least C++20 required but have ${CMAKE_CXX_STANDARD}")
endif ()

add_library(${PROJECT_NAME} SHARED
        )

target_sources(${PROJECT_NAME}
        PUBLIC
        src/library.cpp
        src/library.h
        src/jni_api.h
)


target_compile_definitions(${PROJECT_NAME} PRIVATE LIBRARY_EXPORTS)