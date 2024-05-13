//
// Created by MichaelBrunner on 13/05/2024.
//

#pragma once

#ifdef LIBRARY_EXPORTS
#define JNI_API __declspec(dllexport)
#else
#define JNI_API __declspec(dllimport)
#endif
