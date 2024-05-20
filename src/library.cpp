#include "library.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <ranges>

void hello() {
    std::cout << "Hello, World!" << std::endl;
}

void Java_org_example_ExampleObjectsJni_helloFromCpp(JNIEnv *env, jclass thisObj, jstring message) {
    hello();
    std::ignore = thisObj;
    if (env == nullptr) {
        std::cerr << "JNIEnv is null" << std::endl;
        return;
    }
    const char *nativeString = env->GetStringUTFChars(message, nullptr);
    std::cout << "Hello from C++, Message from Java: " << nativeString << std::endl;
    env->ReleaseStringUTFChars(message, nativeString);
}

void Java_org_example_ExampleObjectsJni_test(JNIEnv *env, jclass thisObj) {
    std::ignore = env;
    std::ignore = thisObj;
    std::cout << "TEST" << std::endl;
}

jobject Java_org_example_Person_createPerson(JNIEnv *env, jclass thisObj, jstring name, jint age) {
    std::ignore = thisObj;
    if (env == nullptr) {
        std::cerr << "JNIEnv is null" << std::endl;
        return nullptr;
    }
    if (name == nullptr) {
        std::cerr << "Name is null" << std::endl;
        return nullptr;
    }
    const char *nativeString = env->GetStringUTFChars(name, nullptr);
    std::cout << "Parameter from Java:" << std::endl;
    std::cout << "nativeString: " << nativeString << std::endl;
    std::cout << "Age: " << age << std::endl;

    std::cout << "Creating new Person object" << std::endl;
    jclass personClass = env->FindClass("org/example/Person");
    jobject newPerson = env->AllocObject(personClass);


    jfieldID nameField = env->GetFieldID(personClass, "name", "Ljava/lang/String;");
    jfieldID ageField = env->GetFieldID(personClass, "age", "I");

    env->SetObjectField(newPerson, nameField, name);
    env->SetIntField(newPerson, ageField, age);

    return newPerson;
}

jstring Java_org_example_Person_getPersonInfo(JNIEnv *env, jobject thisObj, jobject personObj) {
    std::ignore = thisObj;

    if (env == nullptr) {
        std::cerr << "JNIEnv is null" << std::endl;
        return nullptr;
    }
    if (personObj == nullptr) {
        std::cerr << "Person object is null" << std::endl;
        return nullptr;
    }
    jclass personClass = env->GetObjectClass(personObj);
    jfieldID nameFieldID = env->GetFieldID(personClass, "name", "Ljava/lang/String;");
    jfieldID ageFieldID = env->GetFieldID(personClass, "age", "I");

    jstring name = static_cast<jstring>(env->GetObjectField(personObj, nameFieldID));
    jint age = env->GetIntField(personObj, ageFieldID);

    const char *nameStr = env->GetStringUTFChars(name, nullptr);
    // const auto result = std::format("Info from C++ => Name: {}, Age: {}", nameStr, age); GNU compiler does not support std::format
    const auto result = std::string("Info from C++ => Name: ") + nameStr + ", Age: " + std::to_string(age);
    env->ReleaseStringUTFChars(name, nameStr);

    return env->NewStringUTF(result.c_str());
}

void Java_org_example_ExampleObjectsJni_fillTheMap(JNIEnv *env, jclass thisObj, jobject hashMap) {
    std::ignore = thisObj;
    if (env == nullptr) {
        std::cerr << "JNIEnv is null" << std::endl;
        return;
    }
    if (hashMap == nullptr) {
        std::cerr << "HashMap is null" << std::endl;
        return;
    }
    jclass mapClass = env->GetObjectClass(hashMap);
    // signature: (Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object; = (key, value) => value (return value)
    jmethodID putMethod = env->GetMethodID(mapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    jclass integerObject = env->FindClass("java/lang/Integer");
    jmethodID integerConstructor = env->GetMethodID(integerObject, "<init>", "(I)V");

    std::ranges::for_each(std::ranges::iota_view{0, 10'000'000}, [&](const int i) {
        jobject key = env->NewStringUTF(std::to_string(i).c_str()); //
        jobject value = env->NewObject(integerObject, integerConstructor, i);
        env->CallObjectMethod(hashMap, putMethod, key, value);
        env->DeleteLocalRef(key);
        env->DeleteLocalRef(value);
    });

    env->DeleteLocalRef(mapClass);
    env->DeleteLocalRef(hashMap);
}
