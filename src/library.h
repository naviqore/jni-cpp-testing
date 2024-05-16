#pragma once

#include "jni_api.h"
#include "jni.h"

JNI_API void hello();

CXX JNI_API void JNICALL Java_org_example_Main_helloFromCpp(JNIEnv *, jobject, jstring) {

}

