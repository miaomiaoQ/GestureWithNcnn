#include <jni.h>

JNIEXPORT jboolean JNICALL
Java_com_example_dmrf_gesturewithncnn_JniClass_GestureNcnn_InitNcnn(JNIEnv *env, jobject instance,
                                                                    jstring gestureDetectionModelPath_) {

    return true;
}

JNIEXPORT void JNICALL
Java_com_example_dmrf_gesturewithncnn_JniClass_GestureNcnn_Detect(JNIEnv *env, jobject instance,
                                                                  jfloatArray i_, jfloatArray q_,
                                                                  jfloatArray scores_,
                                                                  jintArray a_) {

}

