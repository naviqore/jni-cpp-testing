//
// Created by MichaelBrunner on 13/05/2024.
//

#pragma once

#ifdef _WIN32
    #ifdef LIBRARY_EXPORTS
        #define JNI_API __declspec(dllexport)
    #else
        #define JNI_API __declspec(dllimport)
    #endif
#else
    #ifdef LIBRARY_EXPORTS
        #define JNI_API __attribute__((visibility("default")))
    #else
        #define JNI_API
    #endif
#endif

#ifdef __cplusplus
#define  CXX extern "C"
#else
#define  CXX
#endif