//
// Created by dmrf on 18-4-3.
//
#include <jni.h>
JNIEXPORT void JNICALL
Java_com_example_dmrf_gesturewithncnn_JniClass_SignalProcess_DemoNew(JNIEnv *env,
                                                                     jobject instance) {

    // TODO

}

JNIEXPORT jint JNICALL
Java_com_example_dmrf_gesturewithncnn_JniClass_SignalProcess_DemoL(JNIEnv *env, jobject instance,
                                                                   jshortArray Record_,
                                                                   jdoubleArray DIST_,
                                                                   jdoubleArray tempII_,
                                                                   jdoubleArray tempQQ_) {
    return 0;
}

JNIEXPORT jint JNICALL
Java_com_example_dmrf_gesturewithncnn_JniClass_SignalProcess_DemoR(JNIEnv *env, jobject instance,
                                                                   jshortArray Record_,
                                                                   jdoubleArray DIST_,
                                                                   jdoubleArray tempII_,
                                                                   jdoubleArray tempQQ_) {
    return 0;
}