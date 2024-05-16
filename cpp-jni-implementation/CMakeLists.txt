cmake_minimum_required(VERSION 3.28)
project(cpp_lib
        DESCRIPTION "C++ implementation of JNI interface"
)

if (MSVC)
    # /W4: level of warning output by the compiler to level 4.
    # /WX: treat all compiler warnings as errors. The build process will fail if any warnings are reported by the compiler.
    add_compile_options(/W4 /WX)
elseif (GCC)
    # -Wall: This option enables all the warnings about constructions that some users consider questionable, and that are easy to avoid.
    # -Wextra: This option enables some extra warning flags that are not enabled by -Wall.
    # -pedantic: This option issues all the warnings demanded by strict ISO C and ISO C++.
    # -Werror: This option makes all warnings into errors.
    add_compile_options(-Wall -Wextra -pedantic -Werror)
else ()
    # neither MSVC nor GCC is being used
    # TODO add compiler specific options
    message(using another compiler)
endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_STANDARD LESS 20)
    message(FATAL_ERROR "At least C++20 required but have ${CMAKE_CXX_STANDARD}")
endif ()

if (UNIX AND NOT APPLE)
    include_directories("$ENV{JAVA_HOME}/include/linux")
elseif (APPLE)
    include_directories("$ENV{JAVA_HOME}/include/darwin")
elseif (WIN32)
    message(java home " $ENV{JAVA_HOME}")
    include_directories("$ENV{JAVA_HOME}/include")
    include_directories("$ENV{JAVA_HOME}/include/win32")
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