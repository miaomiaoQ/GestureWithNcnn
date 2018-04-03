//
// Created by dmrf on 18-4-3.
//
#include <jni.h>
#include <string>
#include <fcntl.h>
#include <android/log.h>

#include "mycic/MyCic.h"
#include "sup/support.cpp"

newdemo *demo_data = NULL;

JNIEXPORT void JNICALL
Java_com_example_dmrf_gesturewithncnn_JniClass_SignalProcess_DemoNew(JNIEnv *env,
                                                                     jobject instance) {

    if (demo_data != NULL)
        delete demo_data;
    demo_data = new newdemo();

}

JNIEXPORT jint JNICALL
Java_com_example_dmrf_gesturewithncnn_JniClass_SignalProcess_DemoL(JNIEnv *env,
                                                                   jobject /* this */,
                                                                   jshortArray BUFF,
                                                                   jdoubleArray REDist,
                                                                   jdoubleArray tII,
                                                                   jdoubleArray tQQ) {
    jshort *Buff = (env)->GetShortArrayElements(BUFF, 0);
    jdouble *O_dist = (env)->GetDoubleArrayElements(REDist, 0);
    jdouble *tempII = (env)->GetDoubleArrayElements(tII, 0);
    jdouble *tempQQ = (env)->GetDoubleArrayElements(tQQ, 0);
    double RE = -1;


    short *coL = new short[6600];
    if (demo_data->now > 3) {//过滤每次录音前0.3
        memcpy(coL, demo_data->lastRecordL, 2200 * sizeof(short));        //上一切片
        memcpy(coL + 2200, Buff, 4400 * sizeof(short));        //当前切片
    }
    memcpy(demo_data->lastRecordL, Buff + 2200,
           2200 * sizeof(short));   //为下一窗口保留  recBufSize/2 - LastLength = 2200

    if (demo_data->now > 4) {
        demo(coL, demo_data->now, demo_data->lastL, demo_data->levdIL, demo_data->levdQL, O_dist,
             tempII, tempQQ);

        RE = 1;
    }
//    demo_data->now++;         //后调用的负责加一

    (env)->ReleaseDoubleArrayElements(tQQ, tempQQ, 0);
    (env)->ReleaseDoubleArrayElements(tII, tempII, 0);
    (env)->ReleaseShortArrayElements(BUFF, Buff, 0);
    (env)->ReleaseDoubleArrayElements(REDist, O_dist, 0);

    return RE;

}

JNIEXPORT jint JNICALL
Java_com_example_dmrf_gesturewithncnn_JniClass_SignalProcess_DemoR(JNIEnv *env,
                                                                   jobject /* this */,
                                                                   jshortArray BUFF,
                                                                   jdoubleArray REDist,
                                                                   jdoubleArray tII,
                                                                   jdoubleArray tQQ) {
    jshort *Buff = (env)->GetShortArrayElements(BUFF, 0);
    jdouble *O_dist = (env)->GetDoubleArrayElements(REDist, 0);
    jdouble *tempII = (env)->GetDoubleArrayElements(tII, 0);
    jdouble *tempQQ = (env)->GetDoubleArrayElements(tQQ, 0);

    double RE = -1;

    short *coR = new short[6600];
    if (demo_data->now > 3) {//过滤每次录音前0.3
        memcpy(coR, demo_data->lastRecordR, 2200 * sizeof(short));        //上一切片
        memcpy(coR + 2200, Buff, 4400 * sizeof(short));        //当前切片
    }
    memcpy(demo_data->lastRecordR, Buff + 2200,
           2200 * sizeof(short));   //为下一窗口保留  recBufSize/2 - LastLength = 2200

    if (demo_data->now > 4) {

        demo(coR, demo_data->now, demo_data->lastR, demo_data->levdIR, demo_data->levdQR, O_dist,
             tempII, tempQQ);


        RE = 1;
    }
    demo_data->now++;         //后调用的负责加一

    (env)->ReleaseDoubleArrayElements(tQQ, tempQQ, 0);
    (env)->ReleaseDoubleArrayElements(tII, tempII, 0);
    (env)->ReleaseShortArrayElements(BUFF, Buff, 0);
    (env)->ReleaseDoubleArrayElements(REDist, O_dist, 0);

    return RE;
}