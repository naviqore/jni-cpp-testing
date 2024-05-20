#pragma once


#include "jni_api.h"
#include "jni.h"


/// @brief 
/// @param env 
/// @param thisObj 
/// @param message 
CXX JNI_API void JNICALL Java_org_example_ExampleObjectsJni_helloFromCpp(JNIEnv *env, jclass thisObj, jstring message);


/// @brief 
/// @param env 
/// @param thisObj 
CXX JNI_API void JNICALL Java_org_example_ExampleObjectsJni_test(JNIEnv *env, jclass thisObj);


/// @brief 
/// @param env 
/// @param thisObj 
/// @param name 
/// @param age 
/// @return 
CXX JNI_API jobject JNICALL Java_org_example_Person_createPerson(JNIEnv *env, jclass thisObj, jstring name, jint age);


/// @brief 
/// @param env 
/// @param thisObj 
/// @param personObj 
/// @return 
CXX JNI_API jstring JNICALL Java_org_example_Person_getPersonInfo(JNIEnv *env, jobject thisObj, jobject personObj);

/// @brief 
/// @param env
/// @param thisObj 
/// @param hashMap 
CXX JNI_API void JNICALL Java_org_example_ExampleObjectsJni_fillTheMap(JNIEnv *env, jclass thisObj, jobject hashMap);
