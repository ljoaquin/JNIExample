#include <jni.h>
#include <string>
#include <android/log.h>
#include <sstream>

void log(const char* msg);
void log(std::string msg);

extern "C"
JNIEXPORT jstring JNICALL
Java_com_lj_jnisnippet_MainActivity_getNative(
        JNIEnv *env,
        jobject self)
{
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_lj_jnisnippet_MainActivity_setNative(
        JNIEnv *env,
        jobject self,
        jint num, jstring str)
{
    const char* cstr = env->GetStringUTFChars(str, NULL);

    std::stringstream ss;
    ss << "setNative num:" << num << ", cstr:" << cstr;
    log(ss.str());

    env->ReleaseStringUTFChars(str, cstr);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_lj_jnisnippet_MainActivity_testSetJava(
        JNIEnv *env,
        jobject self)
{
    jstring jstr = env->NewStringUTF("str from c++");

    jclass cls = env->GetObjectClass(self);
    jmethodID id = env->GetMethodID(cls, "setJava", "(ILjava/lang/String;)V");
    env->CallVoidMethod(self, id, 123, jstr);

    env->DeleteLocalRef(jstr);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_lj_jnisnippet_MainActivity_testGetJava(
        JNIEnv *env,
        jobject self)
{
    jclass cls = env->GetObjectClass(self);
    jmethodID id = env->GetMethodID(cls, "getJava", "()Ljava/lang/String;");
    jobject obj = env->CallObjectMethod(self, id);

    const char* cstr = env->GetStringUTFChars((jstring)obj, NULL);

    std::stringstream ss;
    ss << "testGetJava cstr:" << cstr;
    log(ss.str());

    env->ReleaseStringUTFChars((jstring)obj, cstr);
}


void log(const char* msg)
{
    __android_log_write(ANDROID_LOG_DEBUG, "[c++]", msg);
}

void log(std::string msg)
{
    log(msg.c_str());
}
